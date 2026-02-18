#ifndef TIMEDEVENTMANAGER_HPP
#define TIMEDEVENTMANAGER_HPP

#include "jwzsfml.hpp"

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
