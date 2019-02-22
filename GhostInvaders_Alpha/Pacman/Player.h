#pragma once
#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_Image.h"
#include "SDL_Timer.h"
#include "Keyboard.h"
#include "Bullets.h"
#include <vector>
#include <SDL_mixer.h>
using namespace std;

class Player
{
	SDL_Image playerImage;
	Vector2F location;
	int m_iSpeed;
	float shootingTime;
	bool shootActive;
	vector<Bullets*> m_vBullets;
	int bulletCount;

	Mix_Chunk* m_mFire;

public:
	inline SDL_Image GetPlayerImage() { return playerImage; }
	Vector2F GetLocation() { return location; }
	vector<Bullets*>& GetBullets() { return m_vBullets; }
	void SpawnBullet();
	void Draw();
	void Update();

	Player();
	~Player();
};

