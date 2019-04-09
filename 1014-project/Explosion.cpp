#include "Explosion.h"


void Explosion::Update(){


  // Tick the counter
  counter++;

  // move to next frame
  if (counter > 10) {
    epSrcR.x += 34;
    if (counter > 60) {
      canDel = true;
      counter = 0;
    }
  }
}

void Explosion::Render(){
  // If animation is still on going Render explosion
  if (!canDel) {
    SDL_RenderCopy(Game::Instance()->GetRenderer(), epText, &epSrcR, &epDestR);
  }
}

void Explosion::Clean(){
  SDL_DestroyTexture(epText);
  SDL_FreeSurface(epSurf);
}
