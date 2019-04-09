#pragma once
#include <iostream>
#include "SDL_image.h"
#include "Vector2.h"
#include "Game.h"
#include <vector>



class Explosion{
public:
	Explosion();
	~Explosion();

	// Constructor
	Explosion(float epx, float epy, float w, float h){
		epDestR.x = epx;
		epDestR.y = epy;
		epDestR.w = w;
		epDestR.h = h;
		epSurf = IMG_Load("img/Explosion.png");
		epText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), epSurf);
		counter = 0;
		canDel = false;
		
		// Set first frame
		epSrcR.x = 0;
		epSrcR.y = 0;
		epSrcR.w = 34;
		epSrcR.h = 34;

	}

	// Functions
	void Update();
	void Render();
	void Clean();

	int counter;

	// Explosion surface and texture
	SDL_Surface* epSurf;
	SDL_Texture* epText;

	// Explosion Rect
	SDL_Rect epDestR, epSrcR;

	// bool for stop explosion
	bool canDel;

};
