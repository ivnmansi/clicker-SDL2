/**
 * @file config.cpp
 * @author Iván Mansilla
 * @brief SDL configurations and other handling.
 * @version 0.2
 * @date 2025-07-13
 * 
 * 
 */
#include "../inc/config.h"

const char* GAME_TITLE = "SDL2 CLICKER ALPHA";

/**
 * @brief Initialize SDL, create a window and renderer.
 * 
 * @param window 
 * @param renderer 
 * @return int 0 on success, -1 on failure.
 */
int init_SDL(SDL_Window** window, SDL_Renderer** renderer) {

    // try to init SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ){
        SDL_Log("ERROR: SDL could not initiialize. %s\n", SDL_GetError());
        return -1;
    }
    
    // init SDL_image
    if(IMG_Init(IMG_INIT_PNG) == 0){
        SDL_Log("ERROR: SDL_image could not initialize. %s\n", IMG_GetError());
        return -1;
    }

    // init SDL_ttf
    if(TTF_Init() == -1){
        SDL_Log("ERROR: SDL_ttf could not initialize. %s\n", TTF_GetError());
        return -1;
    }

    // create the window and renderer
    *window = SDL_CreateWindow(
        GAME_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
        
    // verify that the window was created
    if(*window == NULL){
        SDL_Log("ERROR: Window could not be created. %s\n", SDL_GetError());
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        SDL_Log("ERROR: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return -1;
    }
        
    return 0;
}