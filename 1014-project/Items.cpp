#include "Items.h"



Items::Items()
{
}


Items::~Items()
{
}

void Items::Update() {
	// Update the bullet size
	bDestR.h = 30;
	bDestR.w = 36;

	bAccel -= 5;

	// Move bullet according to the speed
	bDestR.x += (bSpeed * Game::Instance()->GetDT() + bAccel* Game::Instance()->GetDT());

	// Set bullet location according to the graphics
	bLocation.x = bDestR.x;
}


void Items::Render() {
	// Render bullet graphics
	SDL_RenderCopy(Game::Instance()->GetRenderer(), bText, NULL, &bDestR);

}


void Items::Clean() {
	// Clean bullet graphics
	SDL_FreeSurface(bSurf);
	SDL_DestroyTexture(bText);
}
