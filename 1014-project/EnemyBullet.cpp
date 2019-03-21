#include "EnemyBullet.h"
#include "Game.h"


void EnemyBullet::Update(){
  // Update the bullet size
  ebDestR.h = 30;
	ebDestR.w = 36;

  // Move bullet according to the speed
  ebDestR.x += ebSpeed;

  // Set bullet location according to the graphics
  ebLocation.x = ebDestR.x;
}



void EnemyBullet::Render(){
  // Render enemy bullet graphics
  SDL_RenderCopy(Game::Instance()->GetRenderer(), ebText, NULL, &ebDestR);
}
