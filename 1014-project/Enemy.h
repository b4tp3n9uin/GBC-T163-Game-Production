#pragma once
#include <iostream>
#include <vector>
#include "SDL_image.h"
#include "Vector2.h"
using namespace std;

// enemy direction
enum ENEMYDIRECTION
{
	UP,
	UPLEFT,
	DOWN,
	DOWNLEFT,
	LEFT,
	RIGHT,
	IDLE
};
// enemy type
enum ENEMYTYPE
{
	RED,
	BLUE,
	PURPLE,
	BOSS
};

// prototype for EnemyBullet
class Game;
class EnemyBullet;
class Enemy{
public:
	Enemy();

	// Constructor
	Enemy(float ex, float ey, ENEMYTYPE type){

		// Set enemy image according to enemyType
		SetType(type);

		// Set enemy position
		eDestR.x = ex;
		eDestR.y = ey;
		if (type == RED)
			eDestR.w = eDestR.h = 40;
		else if (type == BLUE)
			eDestR.w = eDestR.h = 60;
		else if (type == PURPLE)
			eDestR.w = eDestR.h = 80;
		else if (type == BOSS)
			eDestR.w = eDestR.h = 150;

	}

	// Enemy type
	ENEMYTYPE eType;

	//Enemy Direction
	ENEMYDIRECTION eDirection;

	//enemy HP
	int eHP;

	//HP guage
	SDL_Rect eHPRect;

	//enelybullet angle
	float eBulletAngle;

	// Enemy rect
	SDL_Rect eDestR;

	// Enemy texture
	SDL_Surface* eSurf;
	SDL_Surface* eSurfGuage;
	SDL_Texture* eText;

	// Enemy speed
	int eSpeed;

	// Enemy turn up and down
	bool eTurn;
	bool canBombDamage = true;

	// Enemy turn up and down Timer
	float eTurnTimer;
	float eBulletTimer;
	// Enemy dead bool
	bool shoot;

	// Enemy bullet
	vector<EnemyBullet*> eBullets;

	// Enemy location
	Vector2 eLocation;

	// Functions
	void SetType(ENEMYTYPE et);
	void SpawnBullet();
	void Render();
	void Update();
	void Clean();


};
