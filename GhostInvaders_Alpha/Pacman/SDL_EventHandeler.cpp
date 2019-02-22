#include "SDL_EventHandeler.h"

#include <SDL.h>
#include "SDL_GameStateManager.h"

#include "Keyboard.h"

void SDL_EventHandeler::PoolEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			break;
		case SDL_WINDOWEVENT:
			TheSDLGameStateManager::Instance()->HandelEvent(&event.window);
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			Keyboard::HandelEvent(&event.key);
			break;
		}
	}
}
