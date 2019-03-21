#include "Bullet.h"
#include "Game.h"



void Bullet::Update(){
  // Update the bullet size
  bDestR.h = 30;
	bDestR.w = 36;

  // Move bullet according to the speed
  bDestR.x += bSpeed;

  // Set bullet location according to the graphics
  bLocation.x = bDestR.x;
}


void Bullet::Render(){
  // Render bullet graphics
  SDL_RenderCopy(Game::Instance()->GetRenderer(), bText, NULL, &bDestR);

}


void Bullet::Clean(){
  // Clean bullet graphics
  SDL_FreeSurface(bSurf);
  SDL_DestroyTexture(bText);
}
