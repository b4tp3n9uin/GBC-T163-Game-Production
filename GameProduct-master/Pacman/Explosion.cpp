#include "Explosion.h"



Explosion::Explosion(Vector2F _exLocation)
{
	cellXY = { 0, 0 };
	explosion.Load("image/Explosionn.png", 4, cellXY);
	exLocation = _exLocation;
}


Explosion::~Explosion()
{
}

void Explosion::Update()
{
	timer += SDL_Timer::GetDT();
	Animation();
}

void Explosion::Draw()
{
	if(!endExplosion)
		explosion.Draw(frame, exLocation, NULL);
}

void Explosion::Animation()
{
	if (timer > 0.3f)
	{
		frame.X = frame.X + 1;
		if (frame.X > 4)
		{
			endExplosion = true;
		}
		timer = 0;
	}
}
