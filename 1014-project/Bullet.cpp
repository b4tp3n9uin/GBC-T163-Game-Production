#include "Bullet.h"
#include "Game.h"



void Bullet::Update(){
  // Update the bullet size
	bDestR.h = 30;
	bDestR.w = 36;

	bDestR.x += (bSpeed * (float)cos((eAngle)*M_PI / 180))/50;
	bDestR.y += (bSpeed * (float)sin((eAngle)*M_PI / 180))/50;
}


void Bullet::Render(){
	// Render bullet graphics
	SDL_RenderCopyEx(Game::Instance()->GetRenderer(), bText, NULL, &bDestR, eAngle, NULL, SDL_FLIP_NONE);
}


void Bullet::Clean(){
  // Clean bullet graphics
  SDL_FreeSurface(bSurf);
  SDL_DestroyTexture(bText);
}

void Bomb::Update()
{
	// Set Bomb location according to the graphics
	bLocation.x = bDestR.x;

	// Move Bomb according to the speed

	if (!trigger)
	{
		// Update the Bomb Timer
		bombTimer += Game::GetDT() * 100;

		if (bombTimer > 200 && bombTimer <= 300)
		{
			// Update the Bomb size
			bDestR.h = 400;
			bDestR.w = 400;
			if (!explode)
			{
				bDestR.x -= 150;
				bDestR.y -= 150;
				explode = true;
			}
			// Update the Bomb explosion
			if (!imageChange)
			{
				bSurf = IMG_Load("img/Bomb.png");
				bText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), bSurf);
				imageChange = true;
			}
		}
		else if (bombTimer > 300)
		{
			trigger = true;
			imageChange = false;
			bDestR.h = 0;
			bDestR.w = 0;
		}
		else
		{
			// Update the Bomb size
			bDestR.h = 50;
			bDestR.w = 50;
			// Update the Bomb move
			bDestR.x += bSpeed * Game::Instance()->GetDT();
		}
	}
}

void Bomb::Render()
{
	if (!trigger)
	{
		// Render Bomb graphics
		SDL_RenderCopy(Game::Instance()->GetRenderer(), bText, NULL, &bDestR);
	}
}

void Bomb::Clean()
{
	// Clean Bomb graphics
	SDL_FreeSurface(bSurf);
	SDL_DestroyTexture(bText);
}
