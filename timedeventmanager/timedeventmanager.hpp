//
//  fusemanager.hpp
//  Ravoxyd_
//
//  Created by John Ziegler on 9/1/24.
//  Copyright © 2024 John Ziegler. All rights reserved.
//

#ifndef TIMEDEVENTMANAGER_HPP
#define TIMEDEVENTMANAGER_HPP

#include "jwzsfml.hpp"

struct Fuse {
    
	Fuse (float delay, bool isDaemon = false, string t = "")
		: tag(t)
		, isOneOff(!isDaemon)
	{
		secondsDelay = seconds(delay);
	}
	
    Fuse (float delay, function<void()> f, bool isDaemon = false, string t = "")
		: func(f)
		, tag(t)
		, isOneOff(!isDaemon)
	{
        secondsDelay = seconds(delay);
//		cout << "Fuse created at " << this << endl; /////////
    }
    
	void fire () {
//		cout<<"Fuse "<<this<<" firing: "; //////////////
//		auto f = func;
//		cout<<"*** ";
//		if (f) {
//			f();
//			cout<<"Func returned. "<<endl;
//		}
//		else cerr<<"Null func."<<endl; /////////
		
		if (func)
			func();
	}

		/* Queue event for removal if true */
    bool isDone = false;
		/* Set isDone after first fire if true */
    bool isOneOff = true;
		/* Skip firing a repeating event, but don't remove it, if false */
    bool isActive = true;
    Time secondsDelay;
    Time readyTime {};
    string tag;
    function<void()> func;
};

using FusePtr = std::shared_ptr<Fuse>;
using FuseWkPtr = std::weak_ptr<Fuse>;


class TimedEventManager
{
public:
	TimedEventManager(int capacity = 100)
	{
		events.reserve(capacity);
		eventCapacity = capacity;
		reset();
	}
	
    void addEvent (FusePtr ev)
	{
		if (events.size() > eventCapacity)
			return;
        ev->readyTime = elapsed + ev->secondsDelay;
        events.push_back(std::move(ev));
		if (ev->tag != "") {
			pendingTags.insert(ev->tag);
		}
    }
    
    void addEvent (float del, function<void(void)> f, bool isDaemon = false, string t = "")
	{
		if (events.size() > eventCapacity)
			return;
        FusePtr ev = std::make_shared<Fuse>(del, f, isDaemon, t);
        ev->readyTime = elapsed + ev->secondsDelay;
        events.push_back(std::move(ev));
		if (t != "") {
			pendingTags.insert(t);
		}
		
		++totalEventsCreated;
	}
	
	void addEvent (float del, function<void(FusePtr)> f, bool isDaemon = false, string t = "")
	{
		if (events.size() > eventCapacity)
			return;
		FusePtr ev = std::make_shared<Fuse>(del, isDaemon, t);
		auto f2 = [thisFuse = ev, f]() { f(thisFuse); };
		ev->func = f2;
		ev->readyTime = elapsed + ev->secondsDelay;
		events.push_back(std::move(ev));
		if (t != "") {
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
		bool firingThisRound = false;
        for (auto& ev : events) {
            if (!ev
				|| ev->isDone
				|| !ev->isActive)
                continue;
            if (ev->readyTime <= t) {
				firingThisRound = true;
                ev->fire();
				// The if (ev) check seems necessary in spite of the earlier
				// if (!ev) continue...
                if (ev && ev->isOneOff)
					ev->isDone = true;
				else if (ev && !ev->isDone)
                    ev->readyTime = t + ev->secondsDelay;
				// THESE LINES SEEMED TO CAUSE ERROR that didn't occur when clearing tags in the erase cycle
//				if (ev->isDone)
//					pendingTags.erase(ev->tag);
            }
        }
		if (!firingThisRound) {
//			auto removeCond = [t](const FusePtr& ev) { return ev->isDone; };
			// I don't know why it was originally [t], but I've removed it: watch for any glitches esp. in LogicCircuits
			auto removeCond = [](const FusePtr& ev) { return ev->isDone; };

			// SOMETHING ABOUT PENDINGTAGS was causing glitches: in LogicGates currently addEventIf has been changed to addEvent to take tags out of equation
			for (auto& ev : events)
				if (removeCond(ev))
					pendingTags.erase(ev->tag);
			// REMOVEIF SEEMED TO CAUSE errors at times that the following loop & single erase didn't cause. but after taking pending tags out of the picture, removeif seems to be working okay
			auto removeItr = remove_if(events.begin(), events.end(), removeCond);
			events.erase(removeItr, events.end());
			
			// THIS LOOP SEEMED more reliable than removeif when tags were in play, but is less efficient with all the single-erase shifting
//			for (auto itr = events.begin(); itr != events.end(); ) {
//				if (removeCond(*itr))
//					itr = events.erase(itr);
//				else ++itr;
//			}
		}
    }
	
	bool isTagActive (const string t)
	{
		return pendingTags.find(t) != pendingTags.end();
	}
	
	void reset()
	{
		clearEvents();
		resetFlagTable();
		elapsed = Time::Zero;
	}
	
    vector<FusePtr>    			events;
	int							eventCapacity;
	unordered_set<string> 		pendingTags;
    Time            			elapsed;
	
	//DEBUG
	int totalEventsCreated;
	
	
	/* The flag table is a sort of unlimited global boolean storage area */
	void resetFlagTable() { flagTable.clear(); }
	
	void gSet (const string& s) { flagTable.insert(s); }
	
	void gUnset (const string& s) { flagTable.erase(s); }
	
	bool gOn (const string& s) { return flagTable.find(s) != flagTable.end(); }
	
	unordered_set<string> 		flagTable;
};


/*
 2. If the daemon manager creates the Daemon internally (e.g., you only pass interval + lambda), then:
 You need the manager to provide the Daemon pointer/reference when creating the lambda internally, so the lambda can capture this or a shared_ptr.
 For example, manager's addEvent(interval, lambda) can internally do:
 cpp
 struct Daemon {
	 std::function<void()> func;
	 bool isDone = false;
 };

 void DaemonManager::addEvent(double interval, std::function<void(Daemon&)> userLambda) {
	 Daemon daemon;
	 daemon.func = [thisDaemon = &daemon, userLambda]() {
		 userLambda(*thisDaemon);
	 };
	 events.push_back(std::move(daemon));
 }
 Then you call:
 cpp
 daemonMgr.addEvent(0.2, [](Daemon& self) {
	 // 'self' is the owning Daemon
	 self.isDone = true;
	 // progressive instructions here
 });
 
 
 
 OR, CREATE DAEMON FIRST:
 auto daemon = std::make_shared<Daemon>();
 daemon->func = [daemon]() {
	 // access owning daemon via captured shared_ptr
	 // do progressive instructions
	 // e.g. mark as done:
	 daemon->isDone = true;
 };
 daemonMgr.addDaemon(daemon);
 */



#endif /* fusemanager_hpp */
