/**
 * @file store.h
 * @author ivan
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * 
 */
#ifndef STORE_H
#define STORE_H

#include <functional>
#include <cmath>
#include "objects.h"
#include "player.h"

class Store;

/**
 * @class Item
 * @brief Represents an item in the store that can be purchased by the player
 */
class Item : public Object {
public:
    Player* playerPtr = nullptr; /*!< Pointer to the player */
    Store* store = nullptr; /*!< Pointer to the store */
    int cost; /*!< Cost of the item */
    std::string description; /*!< Description of the item */
    std::function<void(Player*)> onPurchase; /*!< Function to call when the item is purchased */
    float prob; /*!< Probability of the item appearing in the store */
    int level; /*!< Level of the item */

    Item(std::string id, float x, float y, float width, float height, std::string textureId, 
         int cost, std::string description, std::function<void(Player*)> onPurchase, 
         float prob, Store* store, Player* player);

    void onClick() override;
};

/**
 * @class Store
 * @brief Represents the store where items can be purchased. It manages the items
 */
class Store : public Object {
public:
    ObjectManager* objManager = nullptr; /*!< Pointer to the object manager */
    std::map<std::string, Item*> items; /*!< Map of all items in the store */
    std::vector<Item*> availableItems; /*!< List of available items in the store */

    /**
     * @brief Construct a new Store object
     * 
     * @param x 
     * @param y 
     * @param width 
     * @param height 
     * @param textureId 
     * @param objManager 
     */
    Store(float x, float y, float width, float height, std::string textureId, ObjectManager* objManager)
        : Object("Store", x, y, width, height, textureId), objManager(objManager) {
        objManager->addObject(this);
    }

    void addItem(Item* item);
    void removeItem(const std::string& id);
    Item* getItemById(const std::string& id);
    void makeItemAvailable(const std::string& id, ObjectManager* objManager);
    void makeItemUnavailable(const std::string& id, ObjectManager* objManager);
    void randomizeAvailableItems();
    void updateStore(Player* player);
};

#endif