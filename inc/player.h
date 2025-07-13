#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"

class Player {
    private:
        int points;
        int multiplier;

    public:
        Player() : points(0), multiplier(1) {}
    
    void addPoints(int p) {
        points += p;
    }
    int getPoints() const {
        return points;
    }
    int getMultiplier(){
        return multiplier;
    }
    
};



#endif