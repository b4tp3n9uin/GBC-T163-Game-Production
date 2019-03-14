#include <iostream>
#include "GameState.h"
using namespace std;

int main(int argc, char* argv[]){
	TheSDLScreenHandeler::Instance()->Initialize("Saber Bomb", Size(1024, 768));
	TheSDLGameStateManager::Instance()->SetState(TheGameState::Instance());
	TheSDLGameStateManager::Instance()->Run();
	return 0;
}
