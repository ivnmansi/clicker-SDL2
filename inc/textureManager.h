#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "config.h"

extern const char* TEXTURE_PATH; /*!< Path to the textures directory */

class TextureManager {

    private:
        std::map<std::string, SDL_Texture*> textureMap; /*!< Map of textures, for searching by ID */
        SDL_Renderer** rendererPtr; /*!< Pointer to the SDL renderer*/
    
    public:
        TextureManager() = default;
        TextureManager(SDL_Renderer** renderer){rendererPtr = renderer;}

        int loadTexture(const std::string& id, const std::string& path);
        int searchTexture(const std::string& id);
        void drawTexture(const std::string& id, float x, float y, float width, float height, SDL_Rect* clip = nullptr);
        void clearAllTextures();
        void loadAllTextures(std::string path);
};

#endif