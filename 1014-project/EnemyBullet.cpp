#include "EnemyBullet.h"
#include "Game.h"


void EnemyBullet::Update(){
  // Update the bullet size
	if (eType == RED || eType == BLUE || eType == PURPLE)
	{
		ebDestR.h = 30;
		ebDestR.w = 36;

		// Move bullet according to the speed
		ebDestR.x += ebSpeed * Game::Instance()->GetDT();

		// Set bullet location according to the graphics
		ebLocation.x = ebDestR.x;
	}
	else
	{
		ebDestR.h = 30;
		ebDestR.w = 36;

		// Boss Move bullet according to the speed
		ebDestR.x += (ebSpeed * (float)cos((eAngle)*M_PI / 180))/200;
		ebDestR.y += (ebSpeed * (float)sin((eAngle)*M_PI / 180))/200;
	}
}



void EnemyBullet::Render(){
  // Render enemy bullet graphics
	if (eType == RED || eType == BLUE || eType == PURPLE)
		SDL_RenderCopy(Game::Instance()->GetRenderer(), ebText, NULL, &ebDestR);
	else
		SDL_RenderCopyEx(Game::Instance()->GetRenderer(), ebText, NULL, &ebDestR, eAngle, NULL, SDL_FLIP_NONE);
}

void EnemyBullet::Clean() {
	SDL_FreeSurface(ebSurf);
	SDL_DestroyTexture(ebText);
}
