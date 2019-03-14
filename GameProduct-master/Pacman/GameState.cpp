#include "GameState.h"

void GameState::Initialize()
{
	player = new Player();
	em = new EnemyManager();
	background.Load("image/Background.png", 1, 1);
	locationBG = { 0, 0 };
	speed = 300;

	if (Mix_Init(MIX_INIT_MP3) != 0) // Mixer init success.
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
		Mix_AllocateChannels(16);
		m_mHit = Mix_LoadWAV("sound/Hit.wav");
		Mix_VolumeChunk(m_mHit, 100);
	}
	else
	{
		cout << "Mixer init fail!" << endl;
	}
}

void GameState::Update()
{
	locationBG.X -= SDL_Timer::GetDT() * 50;
	if (locationBG.X < -1024)
		locationBG.X = 0;

	player->Update();
	em->Update();
	for (int i = 0; i < (int)m_vExplosion.size(); i++)
		m_vExplosion[i]->Update();

	CheckCollision();
}


void GameState::Draw()
{
	background.Draw(locationBG, 0.0f);
	player->Draw();
	em->Draw();
	for (int i = 0; i < (int)m_vExplosion.size(); i++)
		m_vExplosion[i]->Draw();
}

void GameState::DeInitialize()
{

}

void GameState::CheckCollision()
{
	for (int b = 0; b < (int)player->GetBullets().size(); b++)
	{
		for (int i = 0; i < (int)em->GetEnemies().size(); i++)
		{
			Bullets* bullet = player->GetBullets()[b];
			Enemy* enemy = em->GetEnemies()[i];

			if(CollisionCheck(bullet->GetImage().GetRect(), enemy->GetImage().GetRect()))
			{
				Mix_PlayChannel(-1, m_mHit, 0);
				m_mHit = Mix_LoadWAV("sound/Hit.wav");
				delete bullet;
				player->GetBullets()[b] = nullptr;
				player->GetBullets().erase(player->GetBullets().begin() + b);

				m_vExplosion.push_back(new Explosion(em->GetEnemies()[i]->GetLocation()));

				delete enemy;
				em->GetEnemies()[i] = nullptr;
				em->GetEnemies().erase(em->GetEnemies().begin() + i);

				goto end;
			}
		}
	}
end:
	player->GetBullets().shrink_to_fit();
	em->GetEnemies().shrink_to_fit();
}
