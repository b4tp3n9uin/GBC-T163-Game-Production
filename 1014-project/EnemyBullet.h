#pragma once
#include <iostream>
#include "SDL_image.h"
#include "Vector2.h"
#include "Game.h"
#include <vector>
using namespace std;

class EnemyBullet{
public:

	// Constructor
	EnemyBullet(float ebx, float eby, ENEMYTYPE _eType, float _eAngle){
		if (_eType == BOSS)
		{
			ebDestR.x = ebx + 30;
			ebDestR.y = eby + 50;
		}
		else
		{
			ebDestR.x = ebx - 10;
			ebDestR.y = eby - 10;
		}
	  eType = _eType;
	  eAngle = _eAngle;
		ebSurf = IMG_Load("img/EnemyBullet.png");
		ebText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), ebSurf);
	}

	// Enemy Bullet rect
	SDL_Rect ebDestR;

	// Enemy Bullet texture
	SDL_Surface* ebSurf;
	SDL_Texture* ebText;

	// enemyType
	ENEMYTYPE eType;

	// EnemyBullet angle
	float eAngle;

	// Enemy Bullet speed
	int ebSpeed = -300;

	// Enemy Bullet location
	Vector2 ebLocation;

	// Update & Render
	void Update();
	void Render();

	// GetBullet location
	Vector2& GetEnemyBulletLocation(){ return ebLocation; }
	void Clean();

};