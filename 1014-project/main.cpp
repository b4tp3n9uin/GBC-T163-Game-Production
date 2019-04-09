#include <iostream>
#include "Game.h"
#include "SDL.h"
#include <stdlib.h>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
using namespace std;

int main(int argc, char* argv[]) {
	// Randomization seed
	srand(time(NULL));

	// Define game obj
	Game::Instance()->Init(
		"PacMan", // window title
		SDL_WINDOWPOS_CENTERED, // x position
		SDL_WINDOWPOS_CENTERED, // y position
		1024, // width
		768, // height
		0 // flag for disply option
	);


	// Game loop
	while (Game::Instance()->Running()) {		// Game m_bRunning
		Game::Instance()->HandleEvents();			// Game HandleEvents
		if (Game::Instance()->Tick()) {    		// Game Tick
			Game::Instance()->Update();
			Game::Instance()->UpdateTimer();
			Game::Instance()->Render();
		}
	}


	// Clean up the game.
	Game::Instance()->Clean();
	system("pause");
	return 0;
}
