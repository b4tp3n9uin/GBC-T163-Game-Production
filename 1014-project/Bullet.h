#pragma once
#include <iostream>
#include "SDL_image.h"
#include "Vector2.h"
#include "Game.h"
#include <vector>
using namespace std;

class Bullet {
public:
	Bullet();
	~Bullet(){};

	// Constructor
	Bullet(float bx, float by){
	  bDestR.x = bx;
	  bDestR.y = by;
		bSurf = IMG_Load("img/PlayerBullet.png");
		bText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), bSurf);
	}

	// Bullet rect
	SDL_Rect bDestR;

	// Bullet texture
	SDL_Surface* bSurf;
	SDL_Texture* bText;

	// Bullet speed
	int bSpeed = 10;

	// Bullet location
	Vector2 bLocation;

	// Update & Render
	void Update();
	void Render();
	void Clean();

	// GetBullet location
	Vector2& GetBulletLocation(){ return bLocation; }


};
