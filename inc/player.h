/**
 * @file player.h
 * @author ivan
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * 
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"

/**
 * @class Player
 * @brief Represents the player state in the game/run
 */
class Player {
    private:
        int points; /*!< Points of the player*/
        int multiplier; /*!< Multiplier for every click*/
        int pointsPerSecond; /*!< Points per second the player gets*/

    public:
        /**
         * @brief Construct a new Player object
         * 
         */
        Player() : points(0), multiplier(1) {}
    
        /**
         * @brief Adds points to the player
         * 
         * @param p Points to add
         */
        void addPoints(int p) {
            points += p;
        }

        /**
         * @brief Get the Points of the player
         * 
         * @return int Points the player has
         */
        int getPoints() const {
            return points;
        }

        /**
         * @brief Get the multiplier of the player
         * 
         * @return int Multiplier of the player
         */
        int getMultiplier(){
            return multiplier;
        }

        /**
         * @brief Adds an amount to the multiplier
         * 
         * @param m Amount to add to the multiplier
         */
        void addMultiplier(int m) {
            multiplier += m;
        }
};



#endif