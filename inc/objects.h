/**
 * @file objects.h
 * @author Iván Mansilla
 * @brief  Object management, creation, and interaction.
 * @version 0.1
 * @date 2025-07-12
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

class ObjectManager{
    private:
        std::map<std::string, Object*> allObjects; /*!< Map of all objects*/
        std::vector<Object*> activeObjects; /*!< List of active objects*/
        std::vector<Object*> clickActiveObjects; /*< List of active and clickable objects*/
    public:
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
};

class Object {
    public:
        std::string id; /*!< ID of the object */
        bool isActive = true; /*!< Whether the object is active */
        float x; /*!< X coordinate of the object */
        float y; /*!< X and Y coordinates of the object */
        float width; /*!< Width of the object */
        float height; /*!< Height of the object */
        std::string textureId; /*!< ID of the texture associated with this object */
        bool isClickable;

        Object() = default;
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

        bool isMouseOver(SDL_Event& e, int mouseX, int mouseY);

        virtual void onRelease() {}
        virtual void onClick() {}
        virtual void onMouseOver() {}
        virtual void onMouseOut() {}

};

#endif
