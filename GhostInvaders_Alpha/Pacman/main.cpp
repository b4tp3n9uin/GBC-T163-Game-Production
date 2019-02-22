// Example program:
// Using SDL2 to create an application window

#include "GameState.h"
int main(int argc, char* argv[])
{
	TheSDLScreenHandeler::Instance()->Initialize("SDL RPG Game", Size(1024, 768));
	TheSDLGameStateManager::Instance()->SetState(TheGameState::Instance());
	TheSDLGameStateManager::Instance()->Run();
	return 0;
}