#pragma once

#include <string>
#include <iostream>
#include "Vector2.h"
#include "Size.h"
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_ScreenHandeler.h"

using namespace std;

struct SDL_Texture;

class SDL_Image
{
protected:
	SDL_Texture* m_Texture = nullptr;
	Size m_TextureSize;
	Vector2 m_CellsXY;
	SDL_Rect dest;

	double m_angle;
	int m_iSprite = 0;	// Which sprite to display for animation.
	int	m_iSpriteMax;	// How many sprites total.
	int	m_iFrame = 0;	// Frame counter.
	int	m_iFrameMax;	// Number of frames per sprite.

public:
	virtual bool Load(const std::string& File);
	virtual void Draw(const Vector2& Location, double angle);
	static bool CollisionCheck(SDL_Rect a, SDL_Rect b)
	{
		bool collision = true;
		if (!((a.x > b.x + b.w) || (a.x + a.w < b.x) || (a.y + a.h < b.y) || (a.y > b.y + b.h)))
			collision = false;
		return collision;
	}
	SDL_Rect GetRect() { return dest; }
	void Animate();
	virtual ~SDL_Image();
};
