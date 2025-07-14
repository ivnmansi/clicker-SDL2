/**
 * @file clickthing.h
 * @author Iván
 * @brief Defines the ClickThing class, which represents an object that the player can click to gain points
 * @version 0.1
 * @date 2025-07-13
 * 
 * 
 */
#ifndef CLICK_THING_H
#define CLICK_THING_H

#include "objects.h"
#include "player.h"

/**
 * @class ClickThing
 * @brief Represents the object the player clicks to gain points
 * 
 */
class ClickThing : public Object {
    public:

        Player* ptrToPlayer = nullptr;

        /**
         * @brief Construct a new Click Thing object
         * 
         * @param ptrToPlayer Pointer to the Player object
         * @param objManager Pointer to the ObjectManager to manage this object
         */
        ClickThing(Player* ptrToPlayer, ObjectManager* objManager) : Object(
            "ClickThing",
            100,
            100,
            200,
            200,
            "example_texture",
            true
        ) {
            this->isActive = true;
            this->isClickable = true;
            objManager->addObject(this);
            this->ptrToPlayer = ptrToPlayer;
        }

        
        /**
         * @brief Action to perform when the object is clicked. In this case add points per click and make a click effect
         * 
         */
        void onClick() override {
            if(!ptrToPlayer) {
                SDL_Log("ptrToPlayer is null");
                return;
            }

            ptrToPlayer->addPoints(1 * ptrToPlayer->getMultiplier());
            printf("Points: %d\n", ptrToPlayer->getPoints());

            resize(this->height-10, this->width-10);
        }

        /**
         * @brief Action to perform when the object is released. In this case resize the object to its original size
         * 
         */
        void onRelease() override {
            resize(this->height+10, this->width+10);
        }
};

#endif