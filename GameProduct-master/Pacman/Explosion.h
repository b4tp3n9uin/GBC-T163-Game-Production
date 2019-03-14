#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_Image.h"
#include "SDL_Timer.h"
#include <vector>

class Explosion
{
	SDL_Image explosion;
	Vector2F exLocation;
	Vector2F frame;
	Vector2 cellXY;
	float timer;
	int m_iSpeed;
	int m_iFrame;
	bool endExplosion;
public:
	Explosion(Vector2F _exLocation);
	~Explosion();
	void Update();
	void Draw();
	void Animation();
	SDL_Image GetImage() { return explosion; }
	bool GetEnd() { return endExplosion; }
	Vector2F GetLocation() { return exLocation; }
	void SetLocation(Vector2F _exLocation) { exLocation = _exLocation; }
};

