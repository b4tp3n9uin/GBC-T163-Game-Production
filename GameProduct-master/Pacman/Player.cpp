#include "Player.h"



void Player::SpawnBullet()
{
	Mix_PlayChannel(-1, m_mFire, 0);
	Vector2F locationB;
	locationB.X = location.X + 40;
	locationB.Y = location.Y + 35;
	m_vBullets.push_back(new Bullets(locationB, location));
}

void Player::Draw()
{
	playerImage.Draw(location, 0.0f);
	for (int i = 0; i < (int)m_vBullets.size(); i++)
		m_vBullets[i]->Draw();
}

void Player::Update()
{
	KeyboardState state = Keyboard::GetState();
	bulletCount = (int)m_vBullets.size();

	if (state.IsKeyDown(Keys::w) && location.Y > 0)
		location.Y -= SDL_Timer::GetDT() * m_iSpeed;
	if (state.IsKeyDown(Keys::s)&& location.Y < 700)
		location.Y += SDL_Timer::GetDT() * m_iSpeed;
	if (state.IsKeyDown(Keys::SPACE) && bulletCount < 1)
	{
		SpawnBullet();
		m_mFire = Mix_LoadWAV("sound/Pew.wav");
		Mix_VolumeChunk(m_mFire, 100);
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
	m_vBullets.shrink_to_fit();
}

Player::Player()
{
	playerImage.Load("image/Player.png", 1, 1);
	location = { 50, 300 };
	m_iSpeed = 200;
	bulletCount = 0;
	if (Mix_Init(MIX_INIT_MP3) != 0) // Mixer init success.
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
		Mix_AllocateChannels(16);
		m_mFire = Mix_LoadWAV("sound/Pew.wav");
		Mix_VolumeChunk(m_mFire, 100);
	}
	else
	{
		cout << "Mixer init fail!" << endl;
	}
}

Player::~Player()
{
	for (int i = 0; i < (int)m_vBullets.size(); i++)
	{
		delete m_vBullets[i];
		m_vBullets[i] = nullptr;
	}
	m_vBullets.clear();
	m_vBullets.shrink_to_fit();
}
