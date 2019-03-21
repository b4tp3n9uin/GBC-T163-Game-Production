#pragma once
#include <iostream>
#include <vector>
#include "SDL_mixer.h"
using namespace std;

class AudioManager{
private:
  vector<Mix_Music*> vMusic;
  vector<Mix_Chunk*> vSounds;
public:
  // Set music volume
	void SetMusicVolume(int v);

  // Start playing BGM
  void PlayMusic(int idx = 0, int loops = -1);

  // Play a single SFX
  void PlaySound(int idx, int channel = -1, int loops = 0);

  // Load BGM from file s
  void LoadMusic(const char* s);

  // Load SFX from file s
	void LoadSound(const char* s);

  // BGM toggle function
	void ToggleMusic();

  // Clear out music in ram
	void ClearMusic();

  // Clear out SFX in ram
	void ClearSounds();
};
