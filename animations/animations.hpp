//
//  animations.hpp
//  Bazjai
//
//  Created by John Ziegler on 3/13/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#include "jwzsfml.hpp"

#include "zsprite.hpp"

/* Make with smart pointers because a vector juggling e.g. enemy
 * sprites will lose Animation::myObj
 */
class Animatable
{
public:
	const vecF& getOrigin () { return ent->getOrigin(); }
	
	void setOrigin (const vecF& ogn) { ent->setOrigin(ogn); }
	
	const vecF& getPosition () { return ent->getPosition(); }
	
	void setPosition (const vecF& pos) { ent->setPosition(pos); }
	
	void move (const vecF& dir) { ent->move(dir); }

	const vecF& getScale () { return ent->getScale(); }
	
	void setScale (const vecF& sc) { ent->setScale(sc); }
	
	void scale (const vecF& sc) { ent->scale(sc); }

	const float getRotation () { return ent->getRotation(); }
	
	void setRotation (float rot) { ent->setRotation(rot); }
	
	void rotate (float rot) { ent->rotate(rot); }
	
	
	/* Sprite will call `setColor`, others will call `setFillColor` */
	virtual void setColor (const Color& c) = 0;
	
	/* These methods will only be overridden by certain subclasses
	 * and will remain empty/irrelevant in others
	 */
	virtual void setTexture (const Texture& tex) { }
	
	virtual void setTextureRect (const IntRect& rect) { }
	
	virtual void setOutlineThickness (float thk) { }
	
	virtual void setOutlineColor (const Color& c) { }
	
	
	Transformable*		ent = nullptr;

	//store tags or ptrs of all Animations pertaining to me
	//isPlayingAnimation
};

using AnimatablePtr = std::shared_ptr<Animatable>;
using AnimatableWkPtr = std::weak_ptr<Animatable>;




class AnimatableSprite: public Animatable
{
public:
	AnimatableSprite ()
	{
		ent = &(spr.s);
	}
	
	void setColor (const Color& c) override { spr.setColor(c); }
	
	void setTexture (const Texture& tex) override { spr.setTexture(tex); }
	
	void setTextureRect (const IntRect& rect) override
	{
		spr.setTextureRect(rect);
	}
	
	ZSprite		spr;
};


template <typename T>
class AnimatableShape: public Animatable
{
public:
	AnimatableShape ()
	{
		ent = &(shape);
	}
	
	void setColor (const Color& c) override { shape.setFillColor(c); }

	virtual void setOutlineThickness (float thk) override
	{
		shape.setOutlineThickness(thk);
	}
	
	virtual void setOutlineColor (const Color& c) override
	{
		shape.setOutlineColor(c);
	}
	
	T			shape;
};



class AnimatableText: public Animatable
{
public:
	AnimatableText ()
	{
		ent = &(txt);
	}
	
	void setColor (const Color& c) override { txt.setFillColor(c); }

	
	virtual void setOutlineThickness (float thk) override
	{
		txt.setOutlineThickness(thk);
	}
	
	virtual void setOutlineColor (const Color& c) override
	{
		txt.setOutlineColor(c);
	}
	
	Text		txt;
};



struct EasingPattern
{
	virtual float operator() (float prog) = 0;
	
	float			duration;
};
// wave-shaped, accelerating


//struct SteadyEasing: public EasingPattern
//{
//	float operator() (float prog) { return prog; }
//};



struct SineEaseInOut: public EasingPattern
{
	//RECONFIG HOW easepattern gets assigned/constructed so duration doesn't have to be mentioned twice in an Animation declaration
	SineEaseInOut (float dur, float steadyRatio=0)
	{
		duration = dur;
		radius = duration / (pi + max(steadyRatio, 0.f));
		steadyLength = steadyRatio * radius;
		apparentLength = steadyLength + 2 * radius;
		sineZone = radius * pi * .5;
	}
	
	float operator() (float prog)
	{
		if (prog > .99)
			return 1;
		auto elapsed = prog * duration;
		float apparentXlat;
		if (elapsed < sineZone)
			apparentXlat = radius - (absCos(elapsed / radius) * radius);
		else if (elapsed < duration - sineZone)
			apparentXlat = elapsed - sineZone + radius;
		else
			apparentXlat = radius + steadyLength + (absSin((elapsed - sineZone - steadyLength) / radius) * radius);
		return apparentXlat / apparentLength;
	}
	
	float 		radius;
	float		apparentLength;
	float		steadyLength;
	float		sineZone;
};



class Animation
{
public:
	virtual ~Animation () = default;
	
	virtual void update (const Time& t)
	{
		auto delta = t - lastActiveTime;
		elapsedWhileActive += delta;
		if (elapsedWhileActive >= totalDuration) {
			if (!looping) {
				endAndReset();
				return;
			}
			else {
				elapsedWhileActive -= totalDuration;
				// FOR VALUEANIMATIONS the startPt will need to be readjusted
			}
		}
		lastActiveTime = t;
		setProgress();
		applyProgress();
	}

	virtual void play (const Time& t) // from start
	{
		lastActiveTime = t;
		isPlaying_ = true;
		// consider executing one frame's worth of progress?
	}
	
	virtual void endAndReset ()
	{
		isPlaying_ = false;
		elapsedWhileActive = Time::Zero;
		setProgress(); //prob redundant: will always be called in update before read from
		//notifyMyObj(tag, "end");
		//lastActiveTime can float, will be reset on next play()?
		// need to know what state to transition to, or the Animatable handles?
	}
	
	virtual void setDuration (float secs)
	{
		elapsedWhileActive = seconds(progress * secs);
		totalDuration = seconds(secs);
		if (easePattern)
			(*(*easePattern)).duration = secs;
		// `progress` is meant to stay the same
	}

	void pauseAnimation ()
	{
		isPlaying_ = false;
		// keep frame/curIdx, elapsed time
	}
	
	void resumeAnimation ()
	{
		// need a `paused` flag? this func calls normal play() if the pause has been erased by override from myObj
		// PROBABLY same as play() only use curIdx as arg for setFrame, or don't set frame at all if knowing that pause() guarantees keeping the same texture
		//time param, to set lastActiveTime when called
		//can we ensure myObj hasn't used a different texture since pause... Animatable has a function to switch to an anim that calls endAndReset on all paused anims
		//how ensure that this was called when in a resume state and not a restart
	}
	

	bool isPlaying () { return isPlaying_; }
	
	//reverse

	AnimatablePtr			myObj;
	string					tag; // unnec if stored in map?
	Time					lastActiveTime;
	Time					elapsedWhileActive;
	Time 					totalDuration;
	float					progress;
	optional<shared_ptr<EasingPattern>>
							easePattern;
	bool					looping = false;
	bool					isPlaying_ = false;
	
protected:
	void setProgress ()
	{
		auto val = elapsedWhileActive / totalDuration;
		if (easePattern)
			progress = (*(*easePattern))(val);
		else progress = val;
	}
	
	virtual void applyProgress () { }
	
};



class ValueAnimation: public Animation
{
public:
	
};



class ColorAnimation: public ValueAnimation
{
public:
	
};



class XformAnimation: public ValueAnimation
{
public:
	virtual ~XformAnimation () = default;
	
};




// MAKE VALUEANIMATION START/DEST visible to these somehow, rather than store copies?
struct PathFunc
{
	virtual ~PathFunc () = default;
	
	virtual vecF operator() (float prog) = 0;
	
	virtual void reset (const vecF& st, const vecF& dest)
	{
		startPt = st;
		destPt = dest;
	}
	
	vecF		startPt;
	vecF		destPt;
};
//path to dest: swirl, zag, point trail


// PASS AN ADJUSTED PROGRESS VALUE THAT'S ALREADY BEEN THROUGH SPEEDPATH?
struct StraightPath: public PathFunc
{
	StraightPath ()
	{
	}
	
	vecF operator() (float prog) override
	{
		return startPt + prog * difVec;
	}
	
	void reset (const vecF& st, const vecF& dest) override
	{
		PathFunc::reset(st, dest);
		difVec = destPt - startPt;
	}
	
	vecF		difVec;
};

struct WavePath: public StraightPath
{
	WavePath (float ampl)
		: StraightPath()
		, amplitude(ampl)
	{ }
	
	vecF operator() (float prog) override
	{
		LineSegment seg {startPt, destPt};
		auto xlat = startPt + prog * difVec;
		auto displacement = sin(prog * seg.length) * amplitude;
		return xlat + pVec(displacement, czdg(seg.angle + 90));
	}
	
	float 				amplitude;
	int 				periods;
	float				periodLength;
};



struct WavePathFreq: public WavePath
{
	/* freq is period size in pixels */
	WavePathFreq (float freq, float ampl)
		: WavePath(ampl)
	{
		auto lgth = hyp(difVec);
		if (freq <= 0)
			freq = lgth;
		periods = round(lgth / freq);
		periodLength = freq;
	}
};



struct WavePathFixedPds: public WavePath
{
	WavePathFixedPds (int pds, float ampl)
		: WavePath(ampl)
	{
		periods = max(pds, 1);
		periodLength = hyp(difVec) / periods;
	}
};


struct ArcPath: public PathFunc
{
	ArcPath ()
	{
		
	}
	
	vecF operator() (float prog) override
	{
	}
	
	vecF		arcCenter;
	float 		arcDif;
	float 		arcRadius;
};
//fixed mid displacement; fixed radius (must be greater than .5 of beeline)


class XlatAnimation: public XformAnimation
{
public:
	void play (const Time& t) override
	{
		Animation::play(t);
		pathFunc->reset(startPt, destPt.value_or(vecF{NAN, NAN}));
	}
	
	void endAndReset () override
	{
		Animation::endAndReset();
		myObj->setPosition(*destPt); ///shouldn't be necessary, but easingfunc not completing path
	}
	
	optional<vecF>					destPt;
	optional<Time>					duration;
	optional<float>					speed;
	
	vecF							startPt;
	shared_ptr<PathFunc>			pathFunc {make_shared<StraightPath>()};
	
protected:
	void applyProgress () override
	{
		myObj->setPosition((*pathFunc)(progress));
	}
};



class DurationAndDest: public XlatAnimation
{
public:
	DurationAndDest (const Time& t, const vecF& dest)
	{
		destPt = dest;
		duration = t;
	}
	
};



class DurationAndSpeed: public XlatAnimation
{
public:
	
};



class SpeedAndDest: public XlatAnimation
{
public:
	
};



class RotationAnimation: public XformAnimation
{
public:
	
};



class ScaleAnimation: public XformAnimation
{
public:
	
};



class ComboAnimation
{
public:
	optional<XlatAnimation>			xlatAnim;
	optional<RotationAnimation>		rotateAnim;
	optional<ScaleAnimation>		scaleAnim;
	optional<ColorAnimation>		colorAnim;
	
	// what defines their joint progress
};



class AnimationFrame
{
public:
	IntRect			texRect;
	vecF			origin;
	float			relDuration;
	float			duration;
	float			nmzdStart;
	float			nmzdEnd;
	//parent anim?
};


class FrameAnimation: public Animation
{
public:
	FrameAnimation (AnimatablePtr parent, vector<AnimationFrame> frameVec)
	: frames(frameVec)
	{
		// tex as param? store tex as pointer to Resources:: tex
		// ensure frameVec has length
		calculateFrameLengths();
	}
	
	void update (const Time& t) override
	{
		auto delta = t - lastActiveTime;
		elapsedWhileActive += delta;
		if (elapsedWhileActive >= totalDuration) {
			if (!looping) {
				endAndReset();
				return;
			}
			else {
				elapsedWhileActive -= totalDuration;
				curIdx = 0;
			}
		}
		lastActiveTime = t;
		setProgress();
		int iterCt = 1;
		for (auto idx = curIdx; idx < frames.size(); ++idx, ++iterCt) {
			if (progress < frames[idx].nmzdEnd
				&& progress >= frames[idx].nmzdStart) {
				if (idx != curIdx) {
					//ensure curIdx always refers to a loaded frame; set it to -1 at animation end?
					/* Don't need to load a new frame if still on curIdx */
					setFrame(idx);
				}
				break;
			}
			if (looping && idx + 1 == frames.size())
				idx = -1;
			/* Forestall infinite loop errors */
			if (iterCt == frames.size()) {
				cerr << "Frame vector (size: " << frames.size() << ") traversed without finding any frame to match the progress (" << progress << ") value. " << endl;
				break;
			}
		}
	}
	
	void setFrame (size_t idx)
	{
		AnimationFrame& frame {frames[idx]};
		myObj->setTextureRect(frame.texRect);
		myObj->setOrigin(frame.origin);
		curIdx = idx;
	}
	
	void play (const Time& t) override
	{
		Animation::play(t);
		myObj->setTexture(tex);
		setFrame(0);
	}
	
	void endAndReset () override
	{
		Animation::endAndReset();
		curIdx = -2;
	}
	
	void setDuration (float secs) override
	{
		Animation::setDuration(secs);
		calculateFrameLengths();
		//curIdx?
	}
	
	vector<AnimationFrame>	frames;
	Texture					tex;
	size_t					curIdx = 0;

	
private:
	void calculateFrameLengths ()
	{
		float relativeCt = 0;
		for (auto& f : frames)
			relativeCt += f.relDuration;
		float relativeUnit = totalDuration.asSeconds() / relativeCt;
		float normalizedTotal = 0;
		for (auto& f : frames) {
			f.duration = f.relDuration * relativeUnit;
			f.nmzdStart = normalizedTotal;
			f.nmzdEnd = f.nmzdStart + f.duration;
			normalizedTotal += f.duration / totalDuration.asSeconds();
		}
	}
};



class AnimationManager
{
public:
	void update (const Time& t)
	{
		elapsed = t;
		for (auto& anim : animations) {
			if (anim->isPlaying())
				anim->update(t);
		}
	}
	//respond to requests to pause/kill anim by tag
	
	//map w/ keys instead?
	vector<shared_ptr<Animation>>	animations;
	Time							elapsed;
};

