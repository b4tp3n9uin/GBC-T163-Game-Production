#pragma once
#include <iostream>
#include <vector>
#include "SDL_image.h"
#include "Vector2.h"
using namespace std;

class Bullet;
class Bomb;
class Player{
public:
	Player(){};

	// Constructor set player location
	Player(float px, float py){
		pDestR.x = px;
		pDestR.y = py;
		isDead = false;
	}

	// Player rect
	SDL_Rect pDestR;

	// Player texture
	SDL_Surface* pSurf;
	SDL_Texture* pText;

	// Player speed
	int pSpeed;

	// player Bomb number
	int pBombNum = 3;
	// player Bullet type
	int bulletType = 0;

	// is Dead
	bool isDead;

	// Player location
	Vector2 pLocation;

	// Vector for all bullets
	vector<Bullet*> m_vBullets;
	int bulletCount;

	// Bomb
	Bomb* m_Bomb;

	// Functions
	void SpawnBullet();
	void SpawnBullet(float angle);
	void SpawnBomb();
	void Render();
	void Update();
	void Clean();
	
	// Get all bullets
	vector<Bullet*>& GetBullets() { return m_vBullets; }

	// Get player location
	Vector2& GetLocation(){ return pLocation; }
};
