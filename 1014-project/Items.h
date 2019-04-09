#pragma once
#include <iostream>
#include "SDL_image.h"
#include "Vector2.h"
#include "Game.h"
#include <vector>
using namespace std;

enum ITEMTYPE
{
	POWER,
	BOMB
};

class Items
{
public:
	Items();
	~Items();
	// Constructor
	Items(float bx, float by, ITEMTYPE items) {
		bDestR.x = bx;
		bDestR.y = by;
		if (items == POWER)
			bSurf = IMG_Load("img/Powerup.png");
		else if (items == BOMB)
			bSurf = IMG_Load("img/PowerupBomb.png");
		bText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), bSurf);
		itemType = items;
	}

	// Item rect
	SDL_Rect bDestR;

	// Item texture
	SDL_Surface* bSurf;
	SDL_Texture* bText;

	// Item speed
	int bSpeed = 300;
	int bAccel = 5;

	// Item Type
	ITEMTYPE itemType;

	// Item location
	Vector2 bLocation;

	// Update & Render
	void Update();
	void Render();
	void Clean();

	// GetBullet location
	Vector2& GetBulletLocation() { return bLocation; }
};

