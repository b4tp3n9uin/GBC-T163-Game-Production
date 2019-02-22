#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_Image.h"
#include "SDL_Timer.h"
#include "Bullets.h"
enum ENEMYDIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
using namespace std;
class Enemy
{
private:
	SDL_Image enemy;
	Vector2F locationE;
	int m_iSpeed;
	float distanceX;
	float originX;
	float bulletTimer;
	float fireTime;
	bool bLive;
	bool shootActive;
	vector<EnemyBullets1*> m_vBullets;
	ENEMYDIRECTION direction;
public:
	Enemy(Vector2F location);
	~Enemy();
	SDL_Image GetImage() { return enemy; }
	void SetImage(SDL_Image explosion) { enemy = explosion; }
	Vector2F GetLocation() { return locationE; }
	float GetDistanceX() { return distanceX; }
	void SetDistanceX(float distance) { this->distanceX = distance; }
	bool GetLive() { return bLive; }
	void SetLive(bool live) { bLive = live; }
	void SetOriginX(float origin) { this->originX = origin; }
	void SetDirection(ENEMYDIRECTION direction) { this->direction = direction; }
	void Update();
	void Draw();
	void SpawnBullet();
};

