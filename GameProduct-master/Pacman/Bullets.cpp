#include "Bullets.h"



Bullets::Bullets(Vector2F _currentLocation, Vector2F _fireLocation)
{
	currentLocation = _currentLocation;
	fireLocation = _fireLocation;
	bulletImage.Load("image/PlayerBullet.png", 1, 1);
	speed = 1.0f;
}

Bullets::Bullets()
{			
}

Bullets::~Bullets()
{
}

void Bullets::Update()
{
	BulletMove();
}

void Bullets::Draw()
{
	bulletImage.Draw(currentLocation, 0.0f);
	SDL_RenderDrawRect(TheSDLScreenHandeler::Instance()->GetRenderer(), &bulletImage.GetRect());
}

void Bullets::BulletMove()
{
	currentLocation.X += speed;
}

EnemyBullets1::EnemyBullets1(Vector2F _currentLocation, Vector2F _fireLocation)
{
	currentLocation = _currentLocation;
	fireLocation = _fireLocation;
	bulletImage.Load("image/EnemyBullet.png", 1, 1);
	speed = 1.0f;
}

EnemyBullets1::EnemyBullets1()
{
}

EnemyBullets1::~EnemyBullets1()
{
}

void EnemyBullets1::Update()
{
	BulletMove();
}

void EnemyBullets1::Draw()
{
	bulletImage.Draw(currentLocation, 0.0f);
	SDL_RenderDrawRect(TheSDLScreenHandeler::Instance()->GetRenderer(), &bulletImage.GetRect());
}

void EnemyBullets1::BulletMove()
{
	currentLocation.X -= speed;
}