/**
 * @file objects.cpp
 * @author Iván Mansilla
 * @brief  Object management, creation, and interaction.
 * @version 0.1
 * @date 2025-07-12
 * 
 * 
 */

#include "../inc/objects.h"
// Ensure the full definition of Object is available

/**
 * @brief Draws the object
 * 
 * @param textureManager Texture manager to handle texture drawing
 */
void Object::drawObject(TextureManager& textureManager){
    textureManager.drawTexture(textureId, x, y, width, height);
}

/**
 * @brief Changes the position of the object
 * 
 * @param x X coordinate of the object
 * @param y Y coordinate of the object
 */
void Object::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

/**
 * @brief Moves the object by a given delta
 * 
 * @param dx Delta X coordinate
 * @param dy Delta Y coordinate
 */
void Object::move(float dx, float dy) {
    x += dx;
    y += dy;
}

/**
 * @brief Resizes the object to new dimensions
 * 
 * @param newWidth 
 * @param newHeight 
 */
void Object::resize(float newWidth, float newHeight) {
    width = newWidth;
    height = newHeight;
}

/**
 * @brief Changes the texture of the object
 * 
 * @param newTextureId ID of the new texture
 * @param textureManager Texture manager to handle texture loading
 * @return int 0 on success, -1 if the texture does not exist
 */
int Object::changeTexture(const std::string& newTextureId, TextureManager& textureManager){
    if(textureManager.searchTexture(newTextureId) == 0) {
        this->textureId = newTextureId;
        return 0;
    }
    else {
        return -1;
    }
}

/**
 * @brief Verifies if the mouse is over the object
 * 
 * @param e Event
 * @param mouseX Position X of the mouse
 * @param mouseY Position Y of the mouse
 * @return true If the mouse is over the object
 * @return false If the mouse is not over the object
 */
bool Object::isMouseOver(SDL_Event& e, int mouseX, int mouseY) {
    return (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
}

/**
 * @brief Creates a new object with the given parameters
 * 
 * @param id ID of the object
 * @param x Position X of the object
 * @param y Position Y of the object
 * @param width Width of the object
 * @param height Height of the object
 * @param textureId Texture ID of the object
 * @param isClickable Is the object clickable
 */
void ObjectManager::createObject(const std::string& id, float x, float y, float width, float height, const std::string& textureId, bool isClickable){

    if(allObjects.find(id) != allObjects.end()){
        SDL_Log("ERROR: Object with ID %s already exists.\n", id.c_str());
        return;
    }

    Object* newObject = new Object(id, x, y, width, height, textureId, isClickable);
    allObjects[id] = newObject;
}

/**
 * @brief Adds an object to the ObjectManager
 * 
 * @param obj 
 */
void ObjectManager::addObject(Object* obj){
    if(allObjects.find(obj->id) != allObjects.end()){
        SDL_Log("ERROR: Object with ID %s already exists.\n", obj->id.c_str());
        return;
    }

    allObjects[obj->id] = obj;
    if(obj->isActive) {
        activeObjects.push_back(obj);
    }
    if(obj->isClickable) {
        clickActiveObjects.push_back(obj);
    }
}

/**
 * @brief Destroys an object by its ID
 * 
 * @param id ID of the object to destroy
 */
void ObjectManager::destroyObject(const std::string& id){

    if(allObjects.find(id) == allObjects.end()){
        SDL_Log("ERROR: Object with ID %s does not exist.\n", id.c_str());
        return;
    }

    Object* obj = allObjects[id];
    if(obj->isActive) {
        deactivateObject(id);
    }
    if(obj->isClickable) {
        makeNonClickable(id);
    }
    allObjects.erase(id);
    delete obj;
}

/**
 * @brief Gets an object by its ID
 * 
 * @param id ID of the object to retrieve
 * @return Object* Pointer to the object if found, nullptr otherwise
 */
Object* ObjectManager::getObjectById(const std::string& id){
    auto obj = allObjects.find(id);
    if (obj != allObjects.end()) {
        return obj->second;
    }
    return nullptr;
}

/**
 * @brief Activates an object by its ID
 * 
 * @param id 
 */
void ObjectManager::activateObject(const std::string& id){
    auto it = allObjects.find(id);
    if( it == allObjects.end()) {
        SDL_Log("ERROR: Object with ID %s does not exist.\n", id.c_str());
        return;
    }

    it->second->isActive = true;
    activeObjects.push_back(it->second);
}

/**
 * @brief Deactivates an object by its ID (gets it removed from the screen)
 * 
 * @param id 
 */
void ObjectManager::deactivateObject(const std::string& id){
    auto it = allObjects.find(id);
    if( it == allObjects.end()) {
        SDL_Log("ERROR: Object with ID %s does not exist.\n", id.c_str());
        return;
    }

    it->second->isActive = false;
    activeObjects.erase(
        std::remove(activeObjects.begin(), activeObjects.end(), it->second),
        activeObjects.end()
    );
    
}

/**
 * @brief Makes an object clickable by its ID
 * 
 * @param id 
 */
void ObjectManager::makeClickable(const std::string& id){
    auto it = allObjects.find(id);
    if( it == allObjects.end()) {
        SDL_Log("ERROR: Object with ID %s does not exist.\n", id.c_str());
        return;
    }

    it->second->isClickable = true;
    clickActiveObjects.push_back(it->second);
}

/**
 * @brief Makes an object non-clickable by its ID
 * 
 * @param id 
 */
void ObjectManager::makeNonClickable(const std::string& id){
    auto it = allObjects.find(id);
    if( it == allObjects.end()) {
        SDL_Log("ERROR: Object with ID %s does not exist.\n", id.c_str());
        return;
    }

    it->second->isClickable = false;
    clickActiveObjects.erase(
        std::remove(clickActiveObjects.begin(), clickActiveObjects.end(), it->second),
        clickActiveObjects.end()
    );
}

/**
 * @brief Destroys all objects managed by the ObjectManager.
 * 
 */
void ObjectManager::destroyAllObjects(){
    for (auto& i : allObjects) {
        delete i.second;
    }
    allObjects.clear();
    activeObjects.clear();
    clickActiveObjects.clear();
}

/**
 * @brief Draws all active objects on the screen.
 * 
 * @param textureManager 
 */
void ObjectManager::drawActiveObjects(TextureManager& textureManager) {
    for (auto& obj : activeObjects) {
        obj->drawObject(textureManager);
    }
}

/**
 * @brief Handles mouse click events for clickable objects.
 * 
 * @param e 
 * @return int 
 */
int ObjectManager::handleMouseClick(SDL_Event& e) {
    int mouseX = e.button.x;
    int mouseY = e.button.y;

    for (auto& obj : clickActiveObjects) {
        if (obj->isMouseOver(e, mouseX, mouseY)) {
            obj->onClick();
            return 0;
        }
    }
    return -1;
}

int ObjectManager::handleMouseRelease(SDL_Event& e) {
    int mouseX = e.button.x;
    int mouseY = e.button.y;

    for (auto& obj : clickActiveObjects) {
        if (obj->isMouseOver(e, mouseX, mouseY)) {
            obj->onRelease();
            return 0;
        }
    }
    return -1;
}


/**
 * @brief Handles mouse over events for clickable objects.
 * 
 * @param e 
 * @return int 
 */
int ObjectManager::handleMouseOver(SDL_Event& e) {
    int mouseX = e.motion.x;
    int mouseY = e.motion.y;

    for (auto& obj : clickActiveObjects) {
        if (obj->isMouseOver(e, mouseX, mouseY)) {
            obj->onMouseOver();
            return 0;
        } else {
            obj->onMouseOut();
        }
    }
    return -1;
}




