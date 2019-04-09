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
	Bullet(float bx, float by, int bType){
	  bDestR.x = bx;
	  bDestR.y = by;
		bSurf = IMG_Load("img/PlayerBullet.png");
		bText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), bSurf);
	}

	Bullet(float bx, float by, int bType, float bAngle) {
		bDestR.x = bx;
		bDestR.y = by;
		bSurf = IMG_Load("img/PlayerBullet.png");
		bText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), bSurf);
		eAngle = bAngle;
	}

	// Bullet rect
	SDL_Rect bDestR;

	// Bullet texture
	SDL_Surface* bSurf;
	SDL_Texture* bText;

	// Bullet speed
	int bSpeed = 300;
	
	// Bullet type
	int bulletType;
	// Bullet angle
	float eAngle;

	// Bullet location
	Vector2 bLocation;

	// Update & Render
	void Update();
	void Render();
	void Clean();
	
	// GetBullet location
	Vector2& GetBulletLocation(){ return bLocation; }


};

class Bomb {
public:
	Bomb();
	~Bomb() {};

	// Constructor
	Bomb(float bx, float by) {
		bDestR.x = bx;
		bDestR.y = by;
		bSurf = IMG_Load("img/BeforeBomb.png");
		bText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), bSurf);
	}

	// Bomb rect
	SDL_Rect bDestR;

	// Bomb texture
	SDL_Surface* bSurf;
	SDL_Texture* bText;

	//Bomb Timer
	float bombTimer;
	bool explode = false;
	bool trigger = false;
	bool imageChange = false;
	// Bomb speed
	int bSpeed = 300;

	// Bomb location
	Vector2 bLocation;

	// Update & Render
	void Update();
	void Render();
	void Clean();

	// GetBomb location
	Vector2& GetBombLocation() { return bLocation; }

};
