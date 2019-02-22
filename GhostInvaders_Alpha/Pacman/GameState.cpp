#include "GameState.h"
#include "Enemy.h"
#include "Vector2.h"

void GameState::Initialize()
{
	player = new Player();
	background.Load("image/Background.png");
	explosion.Load("image/Explosion.png");
	locationBG = { 0, 0 };
	speed = 300;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (j == 0)
			{
				locationE = { 750, (float)(200 + i * 50) };
				Enemy* temp = new Enemy(locationE);
				enemies.push_back(temp);
				enemies[i]->SetDirection(UP);
			}
			else if (j == 1) 
			{
				locationE = { 800, (float)(200 + i * 50) };
				Enemy* temp = new Enemy(locationE);
				enemies.push_back(temp);
				enemies[i]->SetDirection(UP);
			}
			else if (j == 2)
			{
				locationE = { 850, (float)(200 + i * 50) };
				Enemy* temp = new Enemy(locationE);
				enemies.push_back(temp);
				enemies[i]->SetDirection(UP);
			}
			else if (j == 3)
			{
				locationE = { 900, (float)(200 + i * 50) };
				Enemy* temp = new Enemy(locationE);
				enemies.push_back(temp);
				enemies[i]->SetDirection(UP);
			}
			else if (j == 4)
			{
				locationE = { 950, (float)(200 + i * 50) };
				Enemy* temp = new Enemy(locationE);
				enemies.push_back(temp);
				enemies[i]->SetDirection(UP);
			}
		}
	}
}

void GameState::Update()
{
	locationBG.X -= SDL_Timer::GetDT() * 100;
	if (locationBG.X < -1024)
		locationBG.X = 0;


	player->Update();

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update();
		if (enemies[i]->GetLocation().Y > 700 && enemies[i]->GetDistanceX() < 50)
		{
			if (enemies[i]->GetLocation().X < 400)
			{
				for (int j = 0; j < enemies.size(); j++)
				{
					enemies[j]->SetDirection(UP);
				}
			}
			else
			{
				for (int j = 0; j < enemies.size(); j++)
				{
					enemies[j]->SetDirection(LEFT);
				}
			}
		}
		if (enemies[i]->GetLocation().Y < 50 && enemies[i]->GetDistanceX() < 50)
		{
			if (enemies[i]->GetLocation().X < 400)
			{
				for (int j = 0; j < enemies.size(); j++)
				{
					enemies[j]->SetDirection(DOWN);
				}
			}
			else
			{
				for (int j = 0; j < enemies.size(); j++)
				{
					enemies[j]->SetDirection(LEFT);
				}
			}
		}
		if (enemies[i]->GetDistanceX() > 50 && enemies[i]->GetLocation().Y > 300)
		{
			for (int j = 0; j < enemies.size(); j++)
			{
				enemies[j]->SetDirection(UP);
				enemies[j]->SetDistanceX(0);
				enemies[j]->SetOriginX(enemies[j]->GetLocation().X);
			}
		}
		if (enemies[i]->GetDistanceX() > 50 && enemies[i]->GetLocation().Y < 300)
		{
			for (int j = 0; j < enemies.size(); j++)
			{
				enemies[j]->SetDirection(DOWN);
				enemies[j]->SetDistanceX(0);
				enemies[j]->SetOriginX(enemies[j]->GetLocation().X);
			}
		}

		if (enemies[i]->GetLive())
		{
			explosionTime += SDL_Timer::GetDT();

			if (explosionTime > 1.0f)
			{
				delete enemies[i];
				enemies[i] = nullptr;
				enemies.erase(enemies.begin() + i);
				explosionTime = 0.0f;
			}
		}
	}

	int i = 0;

	CheckCollision();
}


void GameState::Draw()
{
	background.Draw(locationBG, 0.0f);
	player->Draw();
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Draw();
	}
}

void GameState::DeInitialize()
{

}

bool GameState::CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));
}

void GameState::CheckCollision()
{
	for (int b = 0; b < (int)player->GetBullets().size(); b++)
	{
		for (int i = 0; i < (int)enemies.size(); i++)
		{
			Bullets* bullet = player->GetBullets()[b];
			if (CircleCollisionTest(bullet->GetLocation().X, bullet->GetLocation().Y,
				enemies[i]->GetLocation().X, enemies[i]->GetLocation().Y, bullet->GetImage().GetRect().w
				, enemies[i]->GetImage().GetRect().w))
			{ 
				delete bullet;
				player->GetBullets()[b] = nullptr;
				player->GetBullets().erase(player->GetBullets().begin() + b);

				enemies[i]->SetImage(explosion);
				enemies[i]->SetLive(true);
				goto end;
			}
		}
	}
end:
	player->GetBullets().shrink_to_fit();
	enemies.shrink_to_fit();
}