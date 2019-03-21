#include "AudioManager.h"
using namespace std;

// Set music volume
void AudioManager::SetMusicVolume(int v){
  v = (v < 0 ? 0 : (v > MIX_MAX_VOLUME ? MIX_MAX_VOLUME : v));
  Mix_VolumeMusic(v);
}


// Start playing BGM
void AudioManager::PlayMusic(int idx, int loops){
  idx = 0;
  loops = -1;
  Mix_PlayMusic(vMusic[idx], loops);
}


// Play a single SFX
void AudioManager::PlaySound(int idx, int channel, int loops){
  channel = -1;
  loops = 0;
  Mix_PlayChannel(channel, vSounds[idx], loops);
}


// Load BGM from file s
void AudioManager::LoadMusic(const char* s){
  // Mix_Music is a music data type
  Mix_Music* m = Mix_LoadMUS(s);

  // If BGM loaded
  if (m != nullptr) {
    // push BGM into the BGM vector
    vMusic.push_back(m);
  } else {
    cout << "Failed to Load File: " << s << '\n';
  }
}


// Load SFX from file s
void AudioManager::LoadSound(const char* s){
  // Chunk stores internal data of a sample
  Mix_Chunk* c = Mix_LoadWAV(s);
  if (c != nullptr) {
    vSounds.push_back(c);
  }else{
    cout << "Failed to Load File: " << s << '\n';
  }
}


// BGM toggle function
void AudioManager::ToggleMusic(){
  if (Mix_PausedMusic() == 1) {
    Mix_ResumeMusic();
  }else{
    Mix_PauseMusic();
  }
}


// Clear out music in ram
void AudioManager::ClearMusic(){
  for (int i = 0; i < (int)vMusic.size(); i++) {
    Mix_FreeMusic(vMusic[i]);
    vMusic[i] = nullptr;
  }
  vMusic.clear();
  vMusic.shrink_to_fit();
}


// Clear out SFX in ram
void AudioManager::ClearSounds(){
  for (int i = 0; i < (int)vSounds.size(); i++) {
    Mix_FreeChunk(vSounds[i]);
    vSounds[i] = nullptr;
  }
  vSounds.clear();
  vSounds.shrink_to_fit();
}
