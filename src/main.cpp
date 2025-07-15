
/**
 * @file main.cpp
 * @author Iván Mansilla
 * @brief Main entry point.
 * @version 0.2
 * @date 2025-07-13
 * 
 * 
 */
#include "../inc/textureManager.h"
#include "../inc/objects.h"
#include "../inc/player.h"
#include "../inc/clickthing.h"
#include "../inc/config.h"
#include "../inc/text.h"
#include "../inc/store.h"


int main( int argc, char* args[] )
{
	srand(time(NULL));

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
	textureManager.loadAllFonts(FONT_PATH);

	// Create the object manager
	ObjectManager objectManager;

	// create the player object
	Player player = Player();

	// Create the clickable thing
	ClickThing clicky = ClickThing(&player,&objectManager);

	// add points text
	Text pointsText = Text(
		"points",
		100, 50, 200, 50,
		"points: 0",
		textureManager.getFont(DEFAULT_FONT),
		{255, 255, 255, 255},
		&objectManager
	);
	objectManager.activateObject("points");
	

	// add points per click text
	Text pointsPerClickText = Text(
		"points_per_click",
		100, 400, 200, 50,
		"Points per click: 1",
		textureManager.getFont(DEFAULT_FONT),
		{255, 255, 255, 255},
		&objectManager
	);
	objectManager.activateObject("points_per_click");


	// make a store
	Store store = Store(
		310,
		10,
		300,
		400,
		"store",
		&objectManager);
	objectManager.activateObject("Store");

	// make an item
	Item exampleItem = Item(
		"example_item",
		"upgrade_example",
		100,
		"An example item for the store.",
		[](Player* player){
			player->addMultiplier(1.0f);
		},
		1,//0-1
		&store, 
		&player
	);

	// make an item
	Item exampleItem2 = Item(
		"example_item2",
		"upgrade_example",
		100,
		"An example item for the store.",
		[](Player* player){
			player->addMultiplier(1.0f);
		},
		1,//0-1
		&store, 
		&player
	);

	// make an item
	Item exampleItem3 = Item(
		"example_item3",
		"upgrade_example",
		100,
		"An example item for the store.",
		[](Player* player){
			player->addMultiplier(1.0f);
		},
		1,//0-1
		&store, 
		&player
	);

	store.randomizeAvailableItems();
	


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

		store.updateStore(&player);

		pointsText.setContent("Points: " + std::to_string(player.getPoints()), renderer);
		pointsPerClickText.setContent("Points per click: " + std::to_string(player.getMultiplier()), renderer);

		objectManager.drawActiveObjects(textureManager);
		objectManager.drawAllTexts(&renderer);
		
		SDL_RenderPresent(renderer);
        SDL_Delay(16);
	}


	
	
	textureManager.clearAllTextures();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
