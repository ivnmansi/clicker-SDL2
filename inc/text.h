/**
 * @file text.h
 * @author ivan
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * 
 */
#ifndef TEXT_H
#define TEXT_H

#include "objects.h"
#include "textureManager.h"

/**
 * @class Text
 * @brief Represents a text object
 */
class Text : public Object {
    public:
        std::string content; /*!< Content */
        TTF_Font** font; /*!< Font */
        SDL_Color color; /*!< Color of the text */
        SDL_Texture* texture = nullptr; /*!< Texture of the text */

        /**
         * @brief Construct a new Text object
         * 
         * @param id 
         * @param x 
         * @param y 
         * @param width 
         * @param height 
         * @param content 
         * @param font 
         * @param color 
         */
        Text(std::string id, float x, float y, float width, float height, std::string content, TTF_Font** font, SDL_Color color) : Object(id, x, y, width, height, "__text__", false) {
            this->content = content;
            this->font = font;
            this->color = color;
        }

        void setContent(const std::string& newContent, SDL_Renderer* renderer);
        void drawText(SDL_Renderer* renderer);

};

#endif