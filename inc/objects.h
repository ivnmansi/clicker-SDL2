/**
 * @file objects.h
 * @author Iván
 * @brief  Object management, creation, and interaction.
 * @version 0.2
 * @date 2025-07-13
 * 
 * 
 */

#ifndef OBJECTS_H
#define OBJECTS_H

#include "config.h"
#include <vector>

#include "textureManager.h"

class TextureManager;
class Object;
class Text;

/**
 * @class ObjectManager
 * @brief Manages the creation, destruction, and interaction of objects in the game.
 */
class ObjectManager{

    public:

        std::map<std::string, Object*> allObjects; /*!< Map of all objects*/
        std::vector<Object*> activeObjects; /*!< List of active objects*/
        std::vector<Object*> clickActiveObjects; /*< List of active and clickable objects*/

        std::vector<Text*> textObjects; /*< List of text objects*/

        ObjectManager() = default;

        void createObject(const std::string& id, float x, float y, float width, float height, const std::string& textureId, bool isClickable = false);
        void addObject(Object* object);
        void destroyObject(const std::string& id);
        Object* getObjectById(const std::string& id);

        void activateObject(const std::string& id);
        void deactivateObject(const std::string& id);

        void makeClickable(const std::string& id);
        void makeNonClickable(const std::string& id);

        void destroyAllObjects();

        void drawActiveObjects(TextureManager& textureManager);

        int handleMouseRelease(SDL_Event& e);
        int handleMouseClick(SDL_Event& e);
        int handleMouseOver(SDL_Event& e);

        void drawAllTexts(SDL_Renderer** rendererPtr);
};

/**
 * @class Object
 * @brief Represents a game object
 */
class Object {
    public:
        std::string id; /*!< ID of the object */
        bool isActive = true; /*!< Whether the project must be draw on the screen*/
        float x; /*!< X coordinate of the object */
        float y; /*!< X and Y coordinates of the object */
        float width; /*!< Width of the object */
        float height; /*!< Height of the object */
        std::string textureId; /*!< ID of the texture associated with this object */
        bool isClickable; /*! Whether the object can be clicked by the player an execute an action*/

        /**
         * @brief Construct a new Object object
         * 
         * @param id 
         * @param x 
         * @param y 
         * @param width 
         * @param height 
         * @param textureId 
         * @param isClickable 
         */
        Object(std::string id, float x, float y, float width, float height, std::string textureId, bool isClickable = false) {
            this->id = id;
            this->isActive = false;
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
            this->textureId = textureId;
            this->isClickable = isClickable;
        }

        virtual ~Object() = default;

        void drawObject(TextureManager& textureManager);
        void setPosition(float x, float y);
        void move(float dx, float dy);
        void resize(float newWidth, float newHeight);
        int changeTexture(const std::string& newTextureId, TextureManager& textureManager);

        bool isMouseOver(int mouseX, int mouseY);

        virtual void onRelease() {}
        virtual void onClick() {}
        virtual void onMouseOver() {}
        virtual void onMouseOut() {}

};

#endif
