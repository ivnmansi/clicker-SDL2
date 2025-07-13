/**
 * @file textureManager.cpp
 * @author Iván Mansilla
 * @brief Texture management, loading, and drawing.
 * @version 0.1
 * @date 2025-07-12
 * 
 * 
 */

#include "../inc/textureManager.h"

const char* TEXTURE_PATH = "assets/textures/"; /*!< Path to the textures directory */

/**
 * @brief Loads a texture from a file and stores it in the texture map.
 * 
 * @param id ID to associate with the texture.
 * @param path Path to the texture file.
 * @return int Returns 0 on success, or a negative value on failure.
 */
 int TextureManager::loadTexture(const std::string& id, const std::string& path){

    // Create a surface from the image file
    // SDL_Surface is used to load the image before converting it to an SDL_Texture
    SDL_Surface* surface = IMG_Load(path.c_str());
    if(!surface){
        SDL_Log("ERROR: Could not load image %s. %s\n", path.c_str(), IMG_GetError());
        return -1;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(*rendererPtr, surface);
    if(!texture){
        SDL_Log("ERROR: Could not create texture from %s. %s\n", path.c_str(), SDL_GetError());
        return -1;
    }
    SDL_FreeSurface(surface);

    // Store the texture in the map with the given ID
    textureMap[id] = texture;
    return 0;
 }

 /**
  * @brief Searches for a texture by its ID.
  * 
  * @param id ID of the texture to search for.
  * @return int 0 if found, or -1 if not found.
  */
 int TextureManager::searchTexture(const std::string& id) {
    if (textureMap.find(id) != textureMap.end()) {
        return 0;
    }
    SDL_Log("ERROR: Texture with ID %s not found.\n", id.c_str());
    return -1;
 }

/**
 * @brief Draws a texture on the screen at the specified position and size.
 * 
 * @param id ID of the texture to draw (must be loaded beforehand).
 * @param x X coordinate of the position to draw the texture.
 * @param y Y coordinate of the position to draw the texture.
 * @param width Width of the texture.
 * @param height Height of the texture.
 * @param clip Clip rectangle to specify a portion of the texture to draw (optional).
 */
 void TextureManager::drawTexture(const std::string& id, float x, float y, float width, float height, SDL_Rect* clip) {

    if(textureMap.find(id) == textureMap.end()) {
        SDL_Log("ERROR: Texture with ID %s not found.\n", id.c_str());
        return;
    }

    SDL_Texture* texture = textureMap[id];
    SDL_Rect destRect = {x,y,width,height};
    SDL_RenderCopy(*rendererPtr, texture, clip, &destRect);
 }

 /**
  * @brief Clears all loaded textures from the texture map.
  * 
  */
 void TextureManager::clearAllTextures(){
    for(auto& i : textureMap){
        SDL_DestroyTexture(i.second);
    }
    textureMap.clear();
 }

 /**
  * @brief Loads all textures from a specified directory. ID will be the file name without extension.
  * 
  * @param path Path to the directory containing texture files.
  */
void TextureManager::loadAllTextures(std::string path){
    SDL_Log("Loading textures from path: %s\n", path.c_str());

    for(auto& file : std::filesystem::directory_iterator(path)){

        std::string extension = file.path().extension().string();
        if(!file.is_regular_file() || (extension != ".png" && extension != ".jpg" && extension != ".jpeg" && extension != ".bmp")){
            continue;
        }

        std::string id = file.path().stem().string(); // Use the file name without extension as ID
        std::string fullPath = file.path().string();

        if(loadTexture(id, fullPath)){
            SDL_Log("Failed to load texture: %s", fullPath.c_str());
        }
        else {
            SDL_Log("Loaded texture: %s", fullPath.c_str());
        }
    }
    SDL_Log("Finished loading textures\n");
 }
