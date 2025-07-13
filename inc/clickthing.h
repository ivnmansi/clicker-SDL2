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

        ClickThing() = default;
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

        void onClick() override {
            if(!ptrToPlayer) {
                SDL_Log("ptrToPlayer is null");
                return;
            }

            ptrToPlayer->addPoints(1 * ptrToPlayer->getMultiplier());
            printf("Points: %d\n", ptrToPlayer->getPoints());

            resize(190, 190);
        }

        void onRelease() override {
            resize(200, 200);
        }
};

#endif