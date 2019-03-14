#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_Image.h"
#include "SDL_Timer.h"
#include "Enemy.h"
#include <vector>
#include <SDL_mixer.h>
#include <time.h>
#include "Player.h"
using namespace std;

class EnemyManager
{
private:
	vector<Enemy*> enemies;
	Vector2 enemyLocation;
	int enemyTimer;
	int countX;
public:
	EnemyManager();
	~EnemyManager();

	void SetEnemies(ENEMYTYPE eType);
	vector<Enemy*>& GetEnemies() { return enemies; }
	inline int RandGetFromIntTo(int fromNum, int toNum)
	{
		return (rand() % (toNum - fromNum + 1)) + fromNum;
	}
	void Draw();
	void Update();
};

