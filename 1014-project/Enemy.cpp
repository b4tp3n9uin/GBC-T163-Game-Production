#include "Enemy.h"
#include "Game.h"
#include "EnemyBullet.h"
using namespace std;


Enemy::Enemy(){
}

void Enemy::SetType(ENEMYTYPE et) {
  if (et == RED) {
    eSurf = IMG_Load("img/Ghost.png");
    eText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), eSurf);
	eType = RED;
	eHP = 1;
	eSpeed = 100;
  }else if (et == BLUE) {
    eSurf = IMG_Load("img/Ghost2.png");
    eText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), eSurf);
	eType = BLUE;
	eHP = 2;
	eSpeed = 100;
  }else if (et == PURPLE) {
    eSurf = IMG_Load("img/Ghost3.png");
    eText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), eSurf);
	eType = PURPLE;
	eHP = 5;
	eSpeed = 50;
  }
  else if (et == BOSS) {
	eSurf = IMG_Load("img/BOSS.png");
	eText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), eSurf);
	eType = BOSS;
	eHP = 30;
	eSpeed = 30;
	eHPRect.x = 300;
	eHPRect.y = 100;
	eHPRect.w = eHP * 5;
	eHPRect.h = 50;
  }
  srand(time(NULL));


}

// Functions
void Enemy::SpawnBullet(){
  // Push a new EnemyBullet into the vector
	if (eType == RED || eType == BLUE || eType == PURPLE)
		eBullets.push_back(new EnemyBullet(eLocation.x + 30, eLocation.y + 20, eType, 0));
	else
		eBullets.push_back(new EnemyBullet(eLocation.x + 30, eLocation.y + 20, eType, eBulletAngle));
}

void Enemy::Update(){
	eTurnTimer += Game::GetDT();
	eBulletTimer += Game::GetDT();

	for (int i = 0; i < (int)eBullets.size(); i++)
	{ // Now update all the bullets.
		eBullets[i]->Update();

		if (eBullets[i]->ebDestR.x < 0 || eBullets[i]->ebDestR.x > 1024 ||
			eBullets[i]->ebDestR.y < 0 || eBullets[i]->ebDestR.y > 768) {
			eBullets[i]->Clean();
			delete eBullets[i];
			eBullets[i] = nullptr;
			eBullets.erase(eBullets.begin() + i);
		}
	}

	eBullets.shrink_to_fit();

  // Update the Enemy size and move and bullet spawn
	switch (eType)
	{
	case RED:
		if (eBulletTimer > rand() % 3 + 2)
		{
			SpawnBullet();
			eBulletTimer = 0;
		}
		eDestR.h = 40;
		eDestR.w = 40;
		eDirection = LEFT;
		break;
	case BLUE:
		if (eBulletTimer > rand() % 3 + 2)
		{
			SpawnBullet();
			eBulletTimer = 0;
		}
		eDestR.h = 60;
		eDestR.w = 60;
		eDirection = LEFT;
		if (eTurn)
			eDirection = UPLEFT;
		else
			eDirection = DOWNLEFT;

		if (eTurnTimer > 1.0f && eTurn)
		{
			eTurn = false;
			eTurnTimer = 0.0f;
		}
		else if (eTurnTimer > 1.0f && !eTurn)
		{
			eTurn = true;
			eTurnTimer = 0.0f;
		}
		break;
	case PURPLE:
		if (eBulletTimer > rand() % 3 + 1)
		{
			SpawnBullet();
			eBulletTimer = 0;
		}
		eDestR.h = 80;
		eDestR.w = 80;
		eDirection = LEFT;
		break;
	case BOSS:
		eHPRect.x = eDestR.x;
		eHPRect.y = eDestR.y - 50;
		eHPRect.w = eHP * 5;
		// Boss bullet spawn
		if (eBulletTimer > 1.5f && eDestR.x < 810)
		{
			for (float i = 0; i < 360; i += 20)
			{
				eBulletAngle = i;
				SpawnBullet();
			}
			eBulletTimer = 0;
		}
		eDestR.h = 150;
		eDestR.w = 150;
		if (eDestR.x > 800)
			eDirection = LEFT;
		else
		{
			if (eTurn)
				eDirection = UP;
			else
				eDirection = DOWN;

			if (eDestR.y < 150)
			{
				eTurn = false;
			}
			else if (eDestR.y > 500)
			{
				eTurn = true;
			}
		}
		break;
	}

	switch (eDirection)
	{
	case UP:
		eDestR.y -= 2* eSpeed * Game::Instance()->GetDT();
		break;
	case DOWN:
		eDestR.y += 2 * eSpeed * Game::Instance()->GetDT();
		break;
	case UPLEFT:
		eDestR.y -= eSpeed * Game::Instance()->GetDT();
		eDestR.x -= eSpeed * Game::Instance()->GetDT();
		break;
	case DOWNLEFT:
		eDestR.y += eSpeed * Game::Instance()->GetDT();
		eDestR.x -= eSpeed * Game::Instance()->GetDT();
		break;
	case LEFT:
		eDestR.x -= eSpeed * Game::Instance()->GetDT();
		break;
	default:
		break;
	}

  // Update Enemy location according to its movement
  eLocation.x = eDestR.x;
  eLocation.y = eDestR.y;
}



void Enemy::Render(){
  // Render Enemy graphics
	SDL_RenderCopy(Game::Instance()->GetRenderer(), eText, NULL, &eDestR);
	for (int i = 0; i < eBullets.size(); i++) {
		eBullets[i]->Render();
	}
	if (eType == BOSS && eHP > 1)
	{
		SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 50, 200, 50, 255);
		SDL_RenderFillRect(Game::Instance()->GetRenderer(), &eHPRect);
	}
}



void Enemy::Clean(){
  // Delete player graphics
	SDL_FreeSurface(eSurf);
	SDL_DestroyTexture(eText);
}
