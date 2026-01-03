//
//  highscore.hpp
//  LetterBallsXC
//
//  Created by John Ziegler on 7/6/24.
//  Copyright © 2024 John Ziegler. All rights reserved.
//

#ifndef highscore_hpp
#define highscore_hpp

#include "jwz.hpp"
//#include "boost/date_time/gregorian/gregorian.hpp"



struct HighScore {

    HighScore() { }
    
    HighScore(int score_, int level_, std::string date_ = "") :
            score(score_),
            level(level_),
            date(date_) { }
    
    string      player {};
    string      date {};
    int         score;
    int         level;
};

#endif /* highscore_hp */
