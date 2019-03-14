#include "SDL_Image.h"

bool SDL_Image::Load(const string& File, int _m_iFrameMax, int _m_iSpriteMax)
{
	// load our image
	m_Texture = IMG_LoadTexture(TheSDLScreenHandeler::Instance()->GetRenderer(), File.c_str());
	if (!m_Texture)
	{
		cout << "SDL_image load failed: %s\n" << endl;
		return true;
	}
	m_iFrameMax = _m_iFrameMax;
	m_iSpriteMax = _m_iSpriteMax;

	// get the width and height of the texture
	SDL_QueryTexture(m_Texture, NULL, NULL, &m_TextureSize.Width, &m_TextureSize.Height);

	return false;
}

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

	center = new Vector2(m_TextureSize.Width / 2, m_TextureSize.Height / 2);

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
	source.x = 0;
	source.y = 0;
	source.w = m_TextureSize.Width / m_iFrameMax;
	source.h = m_TextureSize.Height;

	dest = destination;

	SDL_RenderCopyEx(TheSDLScreenHandeler::Instance()->GetRenderer(), m_Texture, &source, &destination, m_angle, nullptr, SDL_FLIP_NONE);
}

void SDL_Image::Update()
{
	source.x = source.w * m_iSprite;
	Animate();
}

SDL_Image::~SDL_Image()
{
}

bool SDL_Image::Load(const std::string & file, int cellSize, Vector2 CellXY)
{
	bool res = Load(file);
	m_CellSize = cellSize;
	m_CellsXY.X = CellXY.X;
	m_CellsXY.Y = CellXY.Y;
	return res;
}

void SDL_Image::Draw(Vector2 CellXY, const Vector2 & location, bool flip)
{
	//if (cell < 0 || cell >(m_CellsXY.X * m_CellsXY.Y))
	//	printf("Attempting to draw an unknown cell number : %i.\n", cell);

	source.x = 32 * CellXY.X;//(cell % m_CellsXY.X);
	source.y = 32 * CellXY.Y;//(cell / m_CellsXY.Y);
	source.w = 32;// m_CellSize.Width;
	source.h = 32;// m_CellSize.Height;

	dest.x = location.X;
	dest.y = location.Y;
	dest.w = source.w;
	dest.h = source.h;
	if (flip == false)
		SDL_RenderCopyEx(TheSDLScreenHandeler::Instance()->GetRenderer(), m_Texture, &source, &dest, 0, nullptr, SDL_FLIP_NONE);
	else
		SDL_RenderCopyEx(TheSDLScreenHandeler::Instance()->GetRenderer(), m_Texture, &source, &dest, 0, nullptr, SDL_FLIP_HORIZONTAL);
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