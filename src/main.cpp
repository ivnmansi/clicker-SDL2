
/**
 * @file main.cpp
 * @author Iván Mansilla
 * @brief Main entry point.
 * @version 0.1
 * @date 2025-07-12
 * 
 * 
 */
#include "../inc/textureManager.h"
#include "../inc/objects.h"
#include "../inc/player.h"
#include "../inc/clickthing.h"
#include "../inc/config.h"

#

int main( int argc, char* args[] )
{

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	// Init SDL and create a window
	if(init_SDL(&window, &renderer) < 0){
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	
	// Initialize texture manager
	TextureManager textureManager(&renderer);
	textureManager.loadAllTextures(TEXTURE_PATH);

	// Create the object manager
	ObjectManager objectManager;

	// create the player object
	Player player = Player();

	// Create the clickable thing
	ClickThing clicky = ClickThing(&player,&objectManager);
	


	// Basic game loop
	bool running = true;
	SDL_Event e;
	while (running){

		// Poll of events
		while(SDL_PollEvent(&e)){
			// Handle quit event
			if(e.type == SDL_QUIT){
				SDL_Log("Quitting the game...");
				running = false;
				break;
			}

			if(e.type == SDL_MOUSEBUTTONDOWN){
				objectManager.handleMouseClick(e);
			}
			else if(e.type == SDL_MOUSEBUTTONUP){
				objectManager.handleMouseRelease(e);
			}
		}
		SDL_RenderClear(renderer);

		objectManager.drawActiveObjects(textureManager);
		
		SDL_RenderPresent(renderer);
        SDL_Delay(16);
	}


	
	
	textureManager.clearAllTextures();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
