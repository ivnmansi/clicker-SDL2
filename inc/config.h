/**
 * @file config.h
 * @author Iván
 * @brief Config things for the game
 * @version 0.1
 * @date 2025-07-13
 * 
 * 
 */
#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif

#ifndef CONFIG_H
#define CONFIG_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include <algorithm>

/**
 * Screen constants
 */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/**
 * Initialize SDL and window
 */
int init_SDL(SDL_Window** window, SDL_Renderer** renderer);

#endif