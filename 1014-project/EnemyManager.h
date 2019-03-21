#pragma once
#include <iostream>
#include "SDL_image.h"
#include "Vector2.h"
#include "Enemy.h"

#include <vector>
using namespace std;

class EnemyManager{
public:
	EnemyManager();
	~EnemyManager();

	vector<Enemy*> enemies;
	Vector2 enemyLocation;

	// Functions
	void Update();
	void Render();
	void Clean();

	
	vector<Enemy*>& GetEnemies() { return enemies; }
	inline int RandGetFromIntTo(int fromNum, int toNum)
	{
		return (rand() % (toNum - fromNum + 1)) + fromNum;
	}

	// Returns a random x position on the right half of the screen
	int RandX(){
		return rand() % 1200 + 950;
	}

	// Returns a random y position on the right half of the screen
	int RandY(){
		return rand() % 750 + 10;
	}

	int RandE(){
		return rand() % 3 + 0;
	}
};
