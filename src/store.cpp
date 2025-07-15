#include "../inc/store.h"

/**
 * @brief Construct a new Item object
 * 
 * @param id 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 * @param textureId 
 * @param cost 
 * @param description 
 * @param onPurchase 
 * @param prob 
 * @param store 
 * @param player 
 */
Item::Item(std::string id, std::string textureId, int cost, std::string description, std::function<void(Player*)> onPurchase, float prob, Store* store, Player* player)
: Object(id, 380, 140, 90, 90, textureId), cost(cost), description(description), onPurchase(onPurchase), prob(prob), playerPtr(player), store(store) {

    level=1;
    store->addItem(this);
    store->objManager->makeClickable(this->id);
}

/**
 * @brief Executes the item action when clicked. 1st checks if the player has enough points, then calls the onPurchase function. Then increases the cost and level of the item, and randomizes available items in the store.
 * 
 */
void Item::onClick() {
    height = height - 10;
    width = width - 10;

    if(playerPtr->getPoints() < cost) {
        SDL_Log("Not enough points to purchase item '%s' (%d)", id.c_str(), cost);
        return;
    }
    if(onPurchase && playerPtr) {
        onPurchase(playerPtr);
        cost = static_cast<int>(cost * pow(cost, level/2.0));
        level++;
        store->randomizeAvailableItems();
    }
}

void Item::onRelease() {
    height = height + 10;
    width = width + 10;
}

/**
 * @brief Adds an item to the store.
 * 
 * @param item 
 */
void Store::addItem(Item* item) {
    if(items.find(item->id) != items.end()) {
        SDL_Log("ERROR: Item with ID %s already exists in the store.\n", item->id.c_str());
        return;
    }
    items[item->id] = item;

    objManager->addObject(item);
    SDL_Log("Item with ID %s added to the store.\n", item->id.c_str());
}

/**
 * @brief Removes an item from the store by its ID.
 * 
 * @param id 
 */
void Store::removeItem(const std::string& id) {
    auto i = items.find(id);
    if(i == items.end()) {
        SDL_Log("ERROR: Item with ID %s does not exist in the store.\n", id.c_str());
        return;
    }
    items.erase(i);
}

/**
 * @brief Gets a pointer to an item by its ID from the store.
 * 
 * @param id 
 * @return Item* 
 */
Item* Store::getItemById(const std::string& id) {
    auto i = items.find(id);
    if(i == items.end()) {
        SDL_Log("ERROR: Item with ID %s not found in the store.\n", id.c_str());
        return nullptr;
    }
    return i->second;
}

/**
 * @brief Makes an item available in the store by its ID and activates it in the ObjectManager.
 * 
 * @param id 
 * @param objManager 
 */
void Store::makeItemAvailable(const std::string& id){
    Item* item = getItemById(id);
    if(!item) {
        SDL_Log("ERROR: Cannot make item with ID %s available, it does not exist.\n", id.c_str());
        return;
    }

    availableItems.push_back(item);
    objManager->activateObject(id);
}

/**
 * @brief Makes an item unavailable in the store by its ID and deactivates it in the ObjectManager.
 * 
 * @param id 
 * @param objManager 
 */
void Store::makeItemUnavailable(const std::string& id) {
    Item* item = getItemById(id);
    if(!item) {
        SDL_Log("ERROR: Cannot make item with ID %s unavailable, it does not exist.\n", id.c_str());
        return;
    }

    if (item->isActive) {
        objManager->deactivateObject(id);
        availableItems.erase(
            std::remove(availableItems.begin(), availableItems.end(), item),
            availableItems.end()
        );
    }
    else {
        SDL_Log("Item with ID %s is already unavailable\n", id.c_str());
    }
}

/**
 * @brief Randomizes the available items in the store based on their probability.
 * 
 */
void Store::randomizeAvailableItems() {
    
    for (auto& item : availableItems){
        makeItemUnavailable(item->id);
    }
    availableItems.clear();

    std::vector<std::pair<Item*, float>> candidates;

    for (auto& pair : items) {
        Item* item = pair.second;
        float randomValue = static_cast<float>(rand()) / RAND_MAX;
        if (item->prob > randomValue) {
            candidates.push_back({item,randomValue});
        }
    }

    std::random_shuffle(candidates.begin(), candidates.end());

    for(int i = 0; i < 3; i++){
        candidates[i].first->y = 140 + i*80;
        makeItemAvailable(candidates[i].first->id);
    }

    SDL_Log("Randomized available items in the store. %d items available.\n", static_cast<int>(availableItems.size()));
}

/**
 * @brief Updates the store based on the player's points. If the player has less points than the item's cost, it adds "_disabled" to the texture ID.
 * 
 * @param player 
 */
void Store::updateStore(Player* player){
    for (auto& item : availableItems){
        if (player->getPoints() < item->cost){
            if(item->textureId.find("_disabled") == std::string::npos) {
                item->textureId = item->textureId + "_disabled";
            }
        }
        else {
            size_t pos = item->textureId.find("_disabled");
            if(pos != std::string::npos) {
                item->textureId = item->textureId.substr(0, pos);
            }
        }
    }
}