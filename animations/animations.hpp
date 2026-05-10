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
#ifdef SFML_3
	vecF getOrigin () { return ent->getOrigin(); }
	
	vecF getPosition () { return ent->getPosition(); }
	
	vecF getScale () { return ent->getScale(); }
	
	const float getRotation () { return ent->getRotation().asDegrees(); }
	
	void setRotation (float rot) { ent->setRotation(degrees(rot)); }
	
	void rotate (float rot) { ent->rotate(degrees(rot)); }
#else
	const vecF& getOrigin () { return ent->getOrigin(); }
	
	const vecF& getPosition () { return ent->getPosition(); }
	
	const vecF& getScale () { return ent->getScale(); }
	
	const float getRotation () { return ent->getRotation(); }
	
	void setRotation (float rot) { ent->setRotation(rot); }
	
	void rotate (float rot) { ent->rotate(rot); }
#endif
	void setOrigin (const vecF& ogn) { ent->setOrigin(ogn); }
	
	void setPosition (const vecF& pos) { ent->setPosition(pos); }
	
	void move (const vecF& dir) { ent->move(dir); }
	
	void setScale (const vecF& sc) { ent->setScale(sc); }
	
	void scale (const vecF& sc) { ent->scale(sc); }
	
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

using AnimatablePtr = unique_ptr<Animatable>;
//using AnimatablePtr = std::shared_ptr<Animatable>;
//using AnimatableWkPtr = std::weak_ptr<Animatable>;




class AnimatableSprite: public Animatable
{
public:
	AnimatableSprite ()
		: spr(make_unique<ZSprite>(Texture()))
	{
		ent = &(spr->s);
	}
	
	AnimatableSprite (const Texture& tex)
		: spr(make_unique<ZSprite>(tex))
	{
		ent = &(spr->s);
	}
	
	AnimatableSprite (ZSprite& zspr)
		: spr(&zspr)
	{
		ent = &(spr->s);
	}
	
	void setColor (const Color& c) override { spr->setColor(c); }
	
	void setTexture (const Texture& tex) override { spr->setTexture(tex); }
	
	void setTextureRect (const IntRect& rect) override
	{
		spr->setTextureRect(rect);
	}
	
	Pointer<ZSprite>	spr;
//	ZSprite		spr {Texture()};
};


template <typename T>
class AnimatableShape: public Animatable
{
public:
	AnimatableShape ()
		: shape(make_unique<T>())
	{
		ent = shape.get();
	}
	
	void setColor (const Color& c) override { shape->setFillColor(c); }

	virtual void setOutlineThickness (float thk) override
	{
		shape->setOutlineThickness(thk);
	}
	
	virtual void setOutlineColor (const Color& c) override
	{
		shape->setOutlineColor(c);
	}
	
	Pointer<T>			shape;
};



class AnimatableText: public Animatable
{
public:
	AnimatableText ()
		: txt(make_unique<Text>(
#ifdef SFML_3
			  Resources::getDefaultFont()
#endif
								))
	{
		ent = txt.get();
	}
	
	void setColor (const Color& c) override { txt->setFillColor(c); }

	
	virtual void setOutlineThickness (float thk) override
	{
		txt->setOutlineThickness(thk);
	}
	
	virtual void setOutlineColor (const Color& c) override
	{
		txt->setOutlineColor(c);
	}
	
	Pointer<Text>		txt;
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
				elapsedWhileActive = totalDuration;
				computeProgress();
				applyProgress();
				endAndReset();
				return;
			}
			else {
				elapsedWhileActive -= totalDuration;
				// FOR VALUEANIMATIONS the startPt will need to be readjusted
			}
		}
		lastActiveTime = t;
		computeProgress();
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
		computeProgress(); //prob redundant: will always be called in update before read from
		//notifyMyObj(tag, "end");
		//lastActiveTime can float, will be reset on next play()?
		// need to know what state to transition to, or the Animatable handles?
	}
	
	virtual void setDuration (float secs)
	{
		// `progress` is meant to stay the same
		elapsedWhileActive = seconds(progress * secs);
		totalDuration = seconds(secs);
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

	Animatable*				myObj;
//	AnimatablePtr			myObj;
	string					tag; // unnec if stored in map?
	Time					lastActiveTime;
	Time					elapsedWhileActive;
	Time 					totalDuration;
	float					progress;
	bool					looping = false;
	bool					isPlaying_ = false;
	
protected:
	void computeProgress ()
	{
		auto val = elapsedWhileActive / totalDuration;
		val = maybeRunEasing(val);
		if (epsEquals(val, 1, .005)) //MAYBE NOT NCSSY, update could handle
			val = 1;
		progress = val;
	}
	
	virtual float maybeRunEasing (float prog) { return prog; }

	virtual void applyProgress () { }
	
};




// MAKE VALUEANIMATION START/DEST visible to these somehow, rather than store copies?
template<typename ValType>
struct PathFunc
{
	virtual ~PathFunc () = default;
	
	virtual ValType operator() (float prog) = 0;
	
	virtual void reset (const ValType& st, const ValType& dest)
	{
		startPt = st;
		destPt = dest;
	}
	
	ValType		startPt;
	ValType		destPt;
};
//path to dest: swirl, zag, point trail



struct StraightPath: public PathFunc<vecF>
{
//	StraightPath ()
//		: PathFunc()
//	{}
	
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


struct ArcPath: public PathFunc<vecF>
{
	ArcPath ()
	{
		
	}
	
	vecF operator() (float prog) override
	{
		return arcCenter;////////
	}
	
	vecF		arcCenter;
	float 		arcDif;
	float 		arcRadius;
};
//fixed mid displacement; fixed radius (must be greater than .5 of beeline)



struct EasingPattern
{
	virtual float operator() (float prog) = 0;
	
	float			duration;
};
// wave-shaped, accelerating


struct SteadyEasing: public EasingPattern
{
	float operator() (float prog) override { return prog; }
};



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
		auto elapsed = prog * duration;
		float apparentXlat;
		if (elapsed < sineZone)
			apparentXlat = radius - (abs(cos(elapsed / radius)) * radius);
		else if (elapsed < duration - sineZone)
			apparentXlat = elapsed - sineZone + radius;
		else apparentXlat = radius + steadyLength + (abs(sin((elapsed - sineZone - steadyLength) / radius)) * radius);
		return apparentXlat / apparentLength;
	}
	
	float 		radius;
	float		apparentLength;
	float		steadyLength;
	float		sineZone;
};



template<typename ValType>
class ValueAnimation: public Animation
{
public:
	ValType					startVal;
	ValType					destVal;
	EasingPattern*			easePattern = nullptr;
	PathFunc<ValType>*		pathFunc = nullptr;
	
	float maybeRunEasing (float prog) override
	{
		if (easePattern)
			prog = (*easePattern)(prog);
		return prog;
	}
	
	void setDuration (float secs) override
	{
		elapsedWhileActive = seconds(progress * secs);
		totalDuration = seconds(secs);
		if (easePattern)
			easePattern->duration = secs;
	}

};



class ColorAnimation: public ValueAnimation<Color>
{
public:
	void applyProgress () override
	{
//		myObj->setColor((*pathFunc)(progress));   /////////
	}
};


template<typename ValType>
class XformAnimation: public ValueAnimation<ValType>
{
public:
	virtual ~XformAnimation () = default;
	
};




class XlatAnimation: public XformAnimation<vecF>
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
	unique_ptr<PathFunc<vecF>>		pathFunc {make_unique<StraightPath>()};
	
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
		//totalDuration
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



class RotationAnimation: public XformAnimation<float>
{
public:
	void applyProgress () override
	{
//		myObj->setRotation((*pathFunc)(progress));/////
	}
};



class ScaleAnimation: public XformAnimation<vecF>
{
public:
	void applyProgress () override
	{
//		myObj->setScale((*pathFunc)(progress)); /////////
	}
};



class ComboAnimation
{
public:
	// will these take subclasses
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
		computeProgress();
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

