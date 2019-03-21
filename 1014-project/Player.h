#pragma once
#include <iostream>
#include <vector>
#include "SDL_image.h"
#include "Vector2.h"
using namespace std;

class Bullet;
class Player{
public:
	Player(){};
	~Player() ;

	// Constructor set player location
	Player(float px, float py){
		pDestR.x = px;
		pDestR.y = py;
	}

	// Player rect
	SDL_Rect pDestR;

	// Player texture
	SDL_Surface* pSurf;
	SDL_Texture* pText;

	// Player speed
	int pSpeed;


	// Player location
	Vector2 pLocation;

	// Vector for all bullets
	vector<Bullet*> m_vBullets;
	int bulletCount;



	// Functions
	void SpawnBullet();
	void Render();
	void Update();
	void Clean();

	// Get all bullets
	vector<Bullet*>& GetBullets() { return m_vBullets; }

	// Get player location
	Vector2& GetLocation(){ return pLocation; }
};
