#include "Enemy.h"



Enemy::Enemy(Vector2F location)
{
	enemy.Load("image/Ghost.png");
	locationE = { location };
	m_iSpeed = 50;
	distanceX = 0;
	originX = location.X;
	fireTime = rand() % 200 + 200;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (direction == UP)
		locationE.Y -= SDL_Timer::GetDT() * m_iSpeed;
	if (direction == DOWN)
		locationE.Y += SDL_Timer::GetDT() * m_iSpeed;
	if (direction == LEFT)
		locationE.X -= SDL_Timer::GetDT() * m_iSpeed;
	if (direction == RIGHT)
		locationE.X += SDL_Timer::GetDT() * m_iSpeed;

	distanceX = originX - locationE.X;

	bulletTimer += SDL_Timer::GetDT() * 50;

	if (bulletTimer > fireTime)
	{
		srand(time(NULL));
		fireTime = rand() % 500 + 50;
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
}

void Enemy::SpawnBullet()
{
	Vector2F locationB;
	locationB.X = locationE.X - 20;
	locationB.Y = locationE.Y + 15;
	m_vBullets.push_back(new EnemyBullets1(locationB, locationE));
}