#include "SDL_Image.h"

bool SDL_Image::Load(const string& File)
{
	// load our image
	m_Texture = IMG_LoadTexture(TheSDLScreenHandeler::Instance()->GetRenderer(), File.c_str());
	if (!m_Texture)
	{
		cout << "SDL_image load failed: %s\n" << endl;
		return true;
	}

	// get the width and height of the texture
	SDL_QueryTexture(m_Texture, NULL, NULL, &m_TextureSize.Width, &m_TextureSize.Height);

	return false;
}

void SDL_Image::Draw(const Vector2 & Location, double angle)
{
	SDL_Rect destination;
	m_angle = angle;
	destination.x = Location.X;
	destination.y = Location.Y;
	destination.w = m_TextureSize.Width;
	destination.h = m_TextureSize.Height;

	dest = destination;

	SDL_RenderCopyEx(TheSDLScreenHandeler::Instance()->GetRenderer(), m_Texture, NULL, &destination, m_angle, nullptr, SDL_FLIP_NONE);
}

SDL_Image::~SDL_Image()
{
}

void SDL_Image::Animate()
{
	m_iFrame++;
	if (m_iFrame == m_iFrameMax)
	{
		m_iFrame = 0;
		m_iSprite++;
		if (m_iSprite == m_iSpriteMax)
			m_iSprite = 0;
	}
}