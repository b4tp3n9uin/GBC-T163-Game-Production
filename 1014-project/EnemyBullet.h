#pragma once
#include <iostream>
#include "SDL_image.h"
#include "Vector2.h"
#include "Game.h"
#include <vector>
using namespace std;

class EnemyBullet{
public:
	EnemyBullet();
	~EnemyBullet();


	// Constructor
	EnemyBullet(float ebx, float eby){
	  ebDestR.x = ebx;
	  ebDestR.y = eby;
		ebSurf = IMG_Load("img/EnemyBullet.png");
		ebText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), ebSurf);
	}

	// Enemy Bullet rect
	SDL_Rect ebDestR;

	// Enemy Bullet texture
	SDL_Surface* ebSurf;
	SDL_Texture* ebText;

	// Enemy Bullet speed
	int ebSpeed = -20;

	// Enemy Bullet location
	Vector2 ebLocation;

	// Update & Render
	void Update();
	void Render();

	// GetBullet location
	Vector2& GetEnemyBulletLocation(){ return ebLocation; }

};
