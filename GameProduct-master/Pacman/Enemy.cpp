#include "Enemy.h"



Enemy::Enemy(Vector2F location, ENEMYTYPE eType)
{
	if (eType == RED)
		enemy.Load("image/Ghost.png", 1, 1);
	if (eType == BLUE)
		enemy.Load("image/Ghost2.png", 1, 1);
	if (eType == PURPLE)
		enemy.Load("image/Ghost3.png", 1, 1);
	locationE = { location };
	m_iSpeed = 100;
	distanceX = 0;
	originX = location.X;
	fireTime = rand() % 1000 + 100;
	this->eType = eType;
}


Enemy::~Enemy()
{
}

void Enemy::Move(ENEMYTYPE eType)
{
	srand(time(NULL));
	if (eType == RED)
	{
		if (direction == UP)
			locationE.Y -= SDL_Timer::GetDT() * m_iSpeed;
		else if (direction == DOWN)
			locationE.Y += SDL_Timer::GetDT() * m_iSpeed;
		else if (direction == LEFT)
			locationE.X -= SDL_Timer::GetDT() * m_iSpeed;
		else if (direction == RIGHT)
			locationE.X += SDL_Timer::GetDT() * m_iSpeed;
	}
	else if (eType == BLUE)
	{	
		locationE.X -= SDL_Timer::GetDT() * m_iSpeed;
	}
	else if (eType == PURPLE)
	{
		locationE.X -= SDL_Timer::GetDT() * m_iSpeed;
	}
}

void Enemy::Update()
{
	bulletTimer += SDL_Timer::GetDT() * 50;

	if (bulletTimer > fireTime)
	{
		fireTime = rand() % 1000 + 200;
		bulletTimer = 0;

		SpawnBullet();
	}

	for (int i = 0; i < (int)m_vBullets.size(); i++)
	{ // Now update all the bullets.
		m_vBullets[i]->Update();

		if (m_vBullets[i]->currentLocation.X < 0 || m_vBullets[i]->currentLocation.X > 1024 ||
			m_vBullets[i]->currentLocation.Y < 0 || m_vBullets[i]->currentLocation.Y > 768)
		{ // Bullet off-screen and can delete.
			delete m_vBullets[i];
			m_vBullets[i] = nullptr;
			m_vBullets.erase(m_vBullets.begin() + i);
		}
	}
}

void Enemy::Draw()
{
	enemy.Draw(locationE, 0.0f);
	for (int i = 0; i < (int)m_vBullets.size(); i++)
		m_vBullets[i]->Draw();
	SDL_RenderDrawRect(TheSDLScreenHandeler::Instance()->GetRenderer(), &enemy.GetRect());
}

void Enemy::SpawnBullet()
{
	Vector2F locationB;
	locationB.X = locationE.X - 20;
	locationB.Y = locationE.Y + 15;
	m_vBullets.push_back(new EnemyBullets1(locationB, locationE));
}