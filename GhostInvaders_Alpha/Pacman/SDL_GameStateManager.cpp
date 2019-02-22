#include "SDL_GameStateManager.h"

#include <SDL.h>
#include "SDL_EventHandeler.h"
#include "SDL_ScreenHandeler.h"
#include "SDL_Timer.h"

void SDL_GameStateManager::HandelEvent(SDL_WindowEvent* winEvent)
{

}

void SDL_GameStateManager::Update()
{
	//game timer
	SDL_Timer::UpdateTimer();
	//events
	
	TheSDLEventHandeler::Instance()->PoolEvents();

	GameStateManager::Update();
}

void SDL_GameStateManager::Draw()
{
	GameStateManager::Draw();
	TheSDLScreenHandeler::Instance()->Flip();
}
