#include "Game.h"
#include "SDL_ttf.h"

bool Game::Init(const char* title, int xpos, int ypos, int width,	int height, int flags){
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (m_pWindow != 0) {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
      if (m_pRenderer == nullptr) {
        return false;
      }
      if (TTF_Init() == 0) {
        if (IMG_Init(IMG_INIT_PNG) != 0) {
          if (Mix_Init(MIX_INIT_MP3) != 0){
            Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 8192);
          }else{
            cout << "Audio init failed" << '\n';
            return false;
          }
        }else{
          cout << "Image init failed" << '\n';
          return false;
        }
      }else{
        cout << "TTF init failed" << '\n';
        return false;
      }
    }else{
      cout << "Window init failed" << '\n';
      return false; // Window init fail.
    }
  }else {
    return false; // SDL init fail.
  }



  // Create new AudioManager
  pAM = new AudioManager();
  pAM -> SetMusicVolume(30);

  // Create new StateMachine
  pFSM = new StateMachine();

  // Kicks player into title state
  pFSM -> ChangeState(new TitleState());

  // Init m_iKeystates
  m_iKeystates = SDL_GetKeyboardState(NULL);

  // Set running flag to true
  m_bRunning = true;
  return true;

}


bool Game::KeyDown(SDL_Scancode c){
  if (m_iKeystates != nullptr)
  {
    if (m_iKeystates[c] == 1)
      return true;
    else
      return false;
  }
  return false;
}


bool Game::Tick(){
  auto duration = steady_clock::now().time_since_epoch();
  auto count = duration_cast<microseconds>(duration).count();
  int tick = 1000000 / 60;
  if (count % tick != 0){
    if (m_bGotTick == false){
      m_bGotTick = true;
      return true;
    }
    return false;
  }
  else m_bGotTick = false;
  return false;
}

bool Game::m_bGotTick;
unsigned int Game::m_OldTick;
unsigned int Game::m_CurrentTick;

void Game::UpdateTimer()
{
	m_OldTick = m_CurrentTick;
	m_CurrentTick = SDL_GetTicks();
}

float Game::GetDT()
{
	float res = (m_CurrentTick - m_OldTick) / 1000.0f;

	if (res > 0.2f)
		res = 0.2f;

	return res;
}


// SDL HandleEvents
void Game::HandleEvents(){
  SDL_Event event;

  while (SDL_PollEvent(&event)){
    switch (event.type){
    case SDL_QUIT:
      m_bRunning = false;
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (event.button.button == SDL_BUTTON_LEFT){
        m_bLeftMouse = true;
      }
      break;
    case SDL_MOUSEBUTTONUP:
      if (event.button.button == SDL_BUTTON_LEFT){
        m_bLeftMouse = false;
      }
      break;
    case SDL_MOUSEMOTION:
      SDL_GetMouseState(&m_iMouseX, &m_iMouseY);
      break;
    }
  }
}




void Game::Clean(){
	// Clean state
	GetFSM()->Clean();
	SDL_DestroyTexture(m_pText);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	SDL_Quit();
}
