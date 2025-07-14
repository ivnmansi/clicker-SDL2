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
const char* FONT_PATH = "assets/"; /*!< Path to the fonts directory */

/**
 * @brief Adds a texture already loaded to the texture map
 * 
 * @param id 
 * @param texture 
 * @return int 
 */
int TextureManager::addTexture(const std::string& id, SDL_Texture* texture){
    if(textureMap.find(id) != textureMap.end()) {
        SDL_Log("ERROR: Texture with ID %s already exists.\n", id.c_str());
        return -1;
    }

    textureMap[id] = texture;
    return 0;
}
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
        SDL_Log("ERROR: Could not load image '%s'. %s\n", path.c_str(), IMG_GetError());
        return -1;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(*rendererPtr, surface);
    if(!texture){
        SDL_Log("ERROR: Could not create texture from '%s'. %s\n", path.c_str(), SDL_GetError());
        return -1;
    }
    SDL_FreeSurface(surface);

    // Store the texture in the map with the given ID
    if(addTexture(id, texture) != 0) {
        SDL_DestroyTexture(texture);
        return -1;
    }
    SDL_Log("Texture '%s' loaded successfully from '%s'\n", id.c_str(), path.c_str());
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
    
    if(id == "__text__"){
        return; // ignore text textures
    }
    if(textureMap.find(id) == textureMap.end()) {
        SDL_Log("ERROR: Texture with ID %s not found.\n", id.c_str());
        return;
    }

    SDL_Texture* texture = textureMap[id];
    SDL_Rect destRect = {static_cast<int>(x),static_cast<int>(y),static_cast<int>(width),static_cast<int>(height)};
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


int TextureManager::loadFont(const std::string& id, const std::string& path, int size){

    std::string newId = id + std::to_string(size);

    if(fontMap.find(newId) != fontMap.end()) {
        SDL_Log("ERROR: Font with ID %s already exists.\n", newId.c_str());
        return -1;
    }

    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if(!font) {
        SDL_Log("ERROR: Could not load font '%s'. %s\n", path.c_str(), TTF_GetError());
        return -1;
    }

    fontMap[newId] = font;
    SDL_Log("Font '%s' loaded successfully from '%s'\n", newId.c_str(), path.c_str());
    return 0;
}

TTF_Font** TextureManager::getFont(const std::string& id){
    auto i = fontMap.find(id);
    if(i == fontMap.end()) {
        SDL_Log("ERROR: Font with ID %s not found.\n", id.c_str());
        return nullptr;
    }
    return &i->second;
}

void TextureManager::clearAllFonts(){
    for(auto& i : fontMap){
        TTF_CloseFont(i.second);
    }
    fontMap.clear();
}

int TextureManager::loadAllFonts(std::string path){
    SDL_Log("Loading fonts from path: %s\n", path.c_str());

    for(auto& file : std::filesystem::directory_iterator(path)){

        std::string extension = file.path().extension().string();
        if(!file.is_regular_file() || (extension != ".ttf" && extension != ".otf")){
            continue;
        }

        std::string id = file.path().stem().string();
        std::string fullPath = file.path().string();

        if(loadFont(id, fullPath, 24)){
            SDL_Log("Failed to load font: %s", fullPath.c_str());
        }
        else {
            SDL_Log("Loaded font: %s", fullPath.c_str());
        }
    }
    SDL_Log("Finished loading fonts\n");
    return 0;
}