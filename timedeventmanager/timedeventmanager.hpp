#ifndef TIMEDEVENTMANAGER_HPP
#define TIMEDEVENTMANAGER_HPP

#include "jwzsfml.hpp"

#include "zsprite.hpp"
//make with smartptr because a vector juggling sprites will lose
//Animation::myObj
class Animatable : public ZSprite
{
public:
	//store tags or ptrs of all Animations pertaining to me
	//isPlayingAnimation
};  //IAnimatable : Drawable?

using AnimatablePtr = std::shared_ptr<Animatable>;
using AnimatableWkPtr = std::weak_ptr<Animatable>;

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


// make AnimationBase / IAnimation for Xform/color animations
class Animation	// FrameAnimation
{
public:
	Animation (AnimatablePtr parent, vector<AnimationFrame> frameVec)
		: frames(frameVec)
	{
		// tex as param? store tex as pointer to Resources:: tex
		// ensure frameVec has length
		calculateFrameLengths();
	}
	
	void update (const Time& t)
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
	
	void play (const Time& t) // from start
	{
		lastActiveTime = t;
		myObj->setTexture(tex);
		setFrame(0);
		isPlaying_ = true;
	}
	
	void endAndReset ()
	{
		isPlaying_ = false;
		curIdx = -2;
		elapsedWhileActive = Time::Zero;
		setProgress(); //prob redundant: will always be called in update before read from
		//notifyMyObj(tag, "end");
		
		//lastActiveTime can float, will be reset on next play()?
		// need to know what state to transition to, or the Animatable handles?
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
	
	void setDuration (float secs)
	{
		elapsedWhileActive = seconds(progress * secs);
		totalDuration = seconds(secs);
		// `progress` is meant to stay the same
		calculateFrameLengths();
		//curIdx?
	}

	bool isPlaying () { return isPlaying_; }
	//reverse
	
	vector<AnimationFrame>	frames;
	Animatable*				myObj = nullptr;
	Texture					tex;
	string					tag; // unnec if stored in map?
	Time					lastActiveTime;
	Time					elapsedWhileActive;
	Time 					totalDuration;
	float					progress;
	size_t					curIdx = 0;
	bool					looping = false;
	bool					isPlaying_ = false;
	
private:
	void setProgress () { progress = elapsedWhileActive / totalDuration; }
	
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
			if (anim.isPlaying())
				anim.update(t);
		}
	}
	//respond to requests to pause/kill anim by tag
	
	//map w/ keys instead?
	vector<Animation>	animations;
	Time				elapsed;
};




class Fuse;
using FusePtr = std::shared_ptr<Fuse>;
using FuseWkPtr = std::weak_ptr<Fuse>;


class Fuse
{
public:
	static inline bool		debugPrint = false;
	
	Fuse (float delay, bool isDaemon = false, string t = "")
		: tag(t)
		, isOneOff(!isDaemon)
	{
		secondsDelay = seconds(delay);
		maybeDebugPrint("endOfCtor");
	}
	
    Fuse (float delay, function<void()> f, bool isDaemon = false, string t = "")
		: func(f)
		, tag(t)
		, isOneOff(!isDaemon)
	{
        secondsDelay = seconds(delay);
		maybeDebugPrint("endOfCtor");
    }
    
	void fire ()
	{
		if (debugPrint) {
			maybeDebugPrint("firing");
			cout << "\n\t*** ";
			auto f = func;
			if (f) {
				f();
				cout << "Func returned" << endl;
			}
			else cerr << "Null func" << endl;
		}
		
		if (func)
			func();
	}

	function<void()> func;
	string tag;
	Time secondsDelay;
	Time readyTime;
	/* Queue event for removal if true */
    bool isDone = false;
	/* Set isDone after first fire if true */
    bool isOneOff = true;
	/* Skip firing a repeating event, but don't remove it, if false */
    bool isActive = true;
	
private:
	void maybeDebugPrint (string when)
	{
		if (!debugPrint)
			return;
		if (when == "endOfCtor")
			cout << "Fuse created";
		else if (when == "firing")
			cout << "Fuse firing";
		cout << "; tag:" << tag << " address:" << this << " time:"
			<< tS(timestampUs()) << endl;
	}
};



class TimedEventManager
{
public:
	TimedEventManager (int capacity = 100)
	{
		setCapacity(capacity);
		reset();
	}
	
	void setCapacity (int cap)
	{
		events.reserve(cap);
		eventCapacity = cap;
	}
	
    void addEvent (FusePtr ev)
	{
		if (events.size() >= eventCapacity) {
			cerr << "Rejected adding event \"" << ev->tag << "\" at " << toString(elapsed.asSeconds()) << ": full\n";
			return;
		}
        ev->readyTime = elapsed + ev->secondsDelay;
        events.push_back(std::move(ev));
		if (ev->tag != "") {
			pendingTags.insert(ev->tag);
		}
    }
    
    void addEvent (float del, function<void(void)> f, bool isDaemon = false, string t = "")
	{
		if (events.size() >= eventCapacity) {
			cerr << "Rejected adding event \"" << t << "\" at " << toString(elapsed.asSeconds()) << ": full\n";
			return;
		}
        FusePtr ev = std::make_shared<Fuse>(del, f, isDaemon, t);
        ev->readyTime = elapsed + ev->secondsDelay;
        events.push_back(std::move(ev));
		if (t != "") {
			pendingTags.insert(t);
		}
	}
	
	void addEvent (float del, function<void(FusePtr)> f, bool isDaemon = false, string t = "")
	{
		if (events.size() >= eventCapacity) {
			cerr << "Rejected adding event \"" << t << "\" at " << toString(elapsed.asSeconds()) << ": full\n";
			return;
		}
		FusePtr ev = std::make_shared<Fuse>(del, isDaemon, t);
		auto f2 = [thisFuse = ev, f]() { f(thisFuse); };
		ev->func = f2;
		ev->readyTime = elapsed + ev->secondsDelay;
		events.push_back(std::move(ev));
		if (t.length()) {
			pendingTags.insert(t);
		}
	}
	
		/* Only add the event if its tag isn't already pending */
	void addEventIf (FusePtr ev)
	{
		if (!isTagActive(ev->tag)) {
			addEvent(std::move(ev));
		}
	}
	
	void addEventIf (string t, float del, function<void(void)> f, bool isDaemon = false)
	{
		if (!isTagActive(t)) {
			addEvent(del, f, isDaemon, t);
		}
	}
    
    void removeByTag (string t)
	{
        for (auto itr = events.begin(); itr != events.end(); ) {
			if ((*itr)->tag == t) {
				pendingTags.erase(t);
				itr = events.erase(itr);
			}
            else ++itr;
        }
    }
    
    void removeEvent (FusePtr ev)
	{
        for (auto itr = events.begin(); itr != events.end(); ) {
            if (*itr == ev ) {
				pendingTags.erase(ev->tag);
                itr = events.erase(itr);
            }
            else ++itr;
        }
    }
	
	void clearEvents ()
	{
		events.clear();
		pendingTags.clear();
	}
    
    void fireReadyEvents (const Time& t)
	{
		elapsed = t;
		if (events.empty()) {
			return;
		}
        for (auto& ev : events) {
            if (!ev
				|| ev->isDone
				|| !ev->isActive)
                continue;
            if (ev->readyTime <= t) {
                ev->fire();
				// The if (ev) check seems necessary in spite of the earlier
				// if (!ev) continue...
                if (ev && ev->isOneOff)
					ev->isDone = true;
				else if (ev && !ev->isDone)
                    ev->readyTime = t + ev->secondsDelay;
				// THESE LINES SEEMED TO CAUSE ERROR that didn't occur when clearing tags in the erase cycle
				if (ev && ev->isDone)
					pendingTags.erase(ev->tag);
            }
        }
	
		auto removeCond = [](const FusePtr& ev) { return !ev || ev->isDone; };
		auto removeItr = remove_if(events.begin(), events.end(), removeCond);
		events.erase(removeItr, events.end());
    }
	
	bool isTagActive (const string t)
	{
		return pendingTags.count(t);
	}
	
	void reset()
	{
		clearEvents();
		elapsed = Time::Zero;
		resetFlagTable();
	}
	
    vector<FusePtr>    			events;
	unordered_set<string> 		pendingTags;
    Time            			elapsed;
	int							eventCapacity;
	
	
	/* The flag table is a sort of unlimited global boolean storage area */
	void resetFlagTable() { flagTable.clear(); }
	
	void gSet (const string& s) { flagTable.insert(s); }
	
	void gUnset (const string& s) { flagTable.erase(s); }
	
	bool gOn (const string& s) { return flagTable.find(s) != flagTable.end(); }
	
	unordered_set<string> 		flagTable;
};

#endif /* fusemanager_hpp */
