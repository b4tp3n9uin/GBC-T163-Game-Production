#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_Image.h"
#include "SDL_Timer.h"
#include <vector>

using namespace std;

class Bullets
{
	SDL_Image bulletImage;
	Vector2F currentLocation;
	Vector2F fireLocation;
	float speed;
	bool fire;

	friend class Player;

public:
	Bullets(Vector2F currentLocation, Vector2F fireLocation);
	Bullets();
	~Bullets();
	void Update();
	void Draw();
	void BulletMove();
	SDL_Image GetImage(){ return bulletImage; }
	Vector2F GetLocation() { return currentLocation; }
};

class EnemyBullets1
{
	SDL_Image bulletImage;
	Vector2F currentLocation;
	Vector2F fireLocation;
	float speed;
	bool fire;

	friend class Enemy;

public:
	EnemyBullets1(Vector2F currentLocation, Vector2F fireLocation);
	EnemyBullets1();
	~EnemyBullets1();
	void Update();
	void Draw();
	void BulletMove();
	SDL_Image GetImage() { return bulletImage; }
	Vector2F GetLocation() { return currentLocation; }
};