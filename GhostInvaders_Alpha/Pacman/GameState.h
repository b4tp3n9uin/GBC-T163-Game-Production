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
#include <vector>



class GameState : public IGameState
{
private:
	friend Singleton<GameState>;
	GameState() {}
	SDL_Image background;
	SDL_Image explosion;
	Player* player;
	vector<Enemy*> enemies;
	Vector2F locationP = { 0, 0 };
	Vector2F locationBG = { 0, 0 };
	Vector2F locationE = { 0, 0 };
	int speed;
	float explosionTime;
public:
	virtual void Initialize();
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DeInitialize() override;
	void CheckCollision();
	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2);
};

typedef  Singleton<GameState> TheGameState;