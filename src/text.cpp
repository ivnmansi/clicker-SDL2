#include "../inc/text.h"

const char* DEFAULT_FONT = "BitPap24";

Text::Text(std::string id, float x, float y, float width, float height, std::string content, TTF_Font** font, SDL_Color color, ObjectManager* objManager) : Object(id, x, y, width, height, "__text__", false) {
    this->content = content;
    this->font = font;
    this->color = color;
    this->objManager = objManager;
    objManager->addObject(this);
    objManager->textObjects.push_back(this);
}

/**
 * @brief Sets the content of the text object and updates its texture. Textures of text objects are managed by themselves rather than the texture manager.
 * 
 * @param newContent The new content to set.
 * @param renderer The SDL renderer to create the texture.
 */
 void Text::setContent(const std::string& newContent, SDL_Renderer* renderer){
    content = newContent;

    // Free the existing texture if it exists
    if(texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    // Create a surface with the text content
    SDL_Surface* surface = TTF_RenderText_Blended(*font, content.c_str(), color);
    if(!surface) {
        SDL_Log("ERROR: Could not create surface for text '%s'. %s\n", id.c_str(), TTF_GetError());
        return;
    }

    // Create a texture
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!texture) {
        SDL_Log("ERROR: Could not create texture for text '%s'. %s\n", id.c_str(), SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Set the width and height of the text object based on the surface
    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);
 }

 /**
  * @brief Draw the text on the renderer
  * 
  * @param renderer 
  */
 void Text::drawText(SDL_Renderer** renderer) {
    if(!texture) {
        SDL_Log("ERROR: Texture for text '%s' is not set.\n", id.c_str());
        return;
    }

    if(!isActive){
        return;
    }

    SDL_Rect dstRect = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height) };
    SDL_RenderCopy(*renderer, texture, nullptr, &dstRect);
 }