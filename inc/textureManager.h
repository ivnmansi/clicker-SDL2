/**
 * @file textureManager.h
 * @author ivan
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * 
 */
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "config.h"

extern const char* TEXTURE_PATH; /*!< Path to the textures directory */
extern const char* FONT_PATH; /*!< Path to the fonts directory */

/**
 * @class TextureManager
 * @brief Manages textures and fonts in the game
 */
class TextureManager {

    private:
        std::map<std::string, SDL_Texture*> textureMap; /*!< Map of textures, for searching by ID */
        std::map<std::string, TTF_Font*> fontMap; /*!< Map of fonts, for searching by ID */
        SDL_Renderer** rendererPtr; /*!< Pointer to the SDL renderer*/
    
    public:
        TextureManager() = default;
        /**
         * @brief Construct a new Texture Manager object
         * 
         * @param renderer 
         */
        TextureManager(SDL_Renderer** renderer){rendererPtr = renderer;}

        int addTexture(const std::string& id, SDL_Texture* texture);
        int loadTexture(const std::string& id, const std::string& path);
        int searchTexture(const std::string& id);
        void drawTexture(const std::string& id, float x, float y, float width, float height, SDL_Rect* clip = nullptr);
        void clearAllTextures();
        void loadAllTextures(std::string path);

        int loadFont(const std::string& id, const std::string& path, int size);
        TTF_Font** getFont(const std::string& id);
        void clearAllFonts();
        int loadAllFonts(std::string path);

};

#endif