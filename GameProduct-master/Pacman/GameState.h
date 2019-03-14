#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <iostream>

#include "SDL_ScreenHandeler.h"
#include "SDL_GameStateManager.h"

#include "SDL_Image.h"
#include "SDL_Timer.h"
#include "Keyboard.h"
#include "Enemy.h"
#include "Player.h"
#include "Explosion.h"
#include <vector>
#include "EnemyManager.h"


class GameState : public IGameState
{
private:
	friend Singleton<GameState>;
	GameState() {}
	SDL_Image background;
	Player* player;
	EnemyManager* em;
	vector<Explosion*> m_vExplosion;
	Vector2F locationP = { 0, 0 };
	Vector2F locationBG = { 0, 0 };
	Vector2F locationE = { 0, 0 };
	int speed;

	Mix_Chunk* m_mHit;

public:
	virtual void Initialize();
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DeInitialize() override;
	void CheckCollision();
	bool CollisionCheck(SDL_Rect a, SDL_Rect b)
	{
		bool collision = false;
		if ((a.x < b.x + b.w) && (a.x + a.w > b.x) && (a.y + a.h > b.y) && (a.y < b.y + b.h))
			collision = true;
		return collision;
	}
};

typedef  Singleton<GameState> TheGameState;