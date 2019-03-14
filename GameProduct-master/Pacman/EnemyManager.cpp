#include "EnemyManager.h"



EnemyManager::EnemyManager()
{
	enemyTimer = 0;
	srand(time(NULL));
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::SetEnemies(ENEMYTYPE eType)
{
	int randX;
	int randY;
	if (eType == RED)
	{
		for (int i = 0; i < 10; i++)
		{
			if (i % 2 == 0)
			{
				enemyLocation = { 900, 400 + i * 30 };
				enemies.push_back(new Enemy(enemyLocation, RED));
			}
			else
			{
				enemyLocation = { 950, 400 + (i - 1) * 30 };
				enemies.push_back(new Enemy(enemyLocation, RED));
			}
		}
	}

	if (eType == BLUE)
	{
		randY = RandGetFromIntTo(100, 600);
		enemyLocation = { 1000, randY };
		enemies.push_back(new Enemy(enemyLocation, BLUE));
	}

	if (eType == PURPLE)
	{
		randY = RandGetFromIntTo(100, 600);
		enemyLocation = { 1000, randY };
		enemies.push_back(new Enemy(enemyLocation, PURPLE));
	}
}

void EnemyManager::Draw()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Draw();
	}
}

void EnemyManager::Update()
{
	enemyTimer++;
	cout << enemyTimer << endl;
	if (enemyTimer % 100 == 0 && enemyTimer < 150)
	{
		SetEnemies(RED);
	}
	
	if (enemyTimer % 1000 == 0 && enemyTimer < 30000)
	{
		SetEnemies(BLUE);
	}

	if (enemyTimer % 1500 == 0 && enemyTimer < 30000)
	{
		SetEnemies(PURPLE);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update();
		enemies[i]->Move(enemies[i]->GetEType());
		if (enemies[i]->GetEType() == RED && enemies[i]->GetLocation().Y < 50)
		{
			for (int j = 0; j < enemies.size(); j++)
			{
				enemies[j]->SetDirection(DOWN);
			}
		}
		if (enemies[i]->GetEType() == RED && enemies[i]->GetLocation().Y > 668)
		{
			for (int j = 0; j < enemies.size(); j++)
			{
				enemies[j]->SetDirection(UP);
			}
		}
	}
}