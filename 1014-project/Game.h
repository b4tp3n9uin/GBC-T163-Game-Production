#pragma once
#include <chrono>
#include <iostream>
#include "AudioManager.h"
#include "FSM.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
using namespace std;
using namespace chrono;

class Game {
private:
	// Variables
	bool m_bRunning;
	bool m_bGotTick;
	bool m_bLeftMouse = false;
	const Uint8* m_iKeystates;
	int m_iMouseX, m_iMouseY;

	// SDL
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Surface* m_pSurf;
	SDL_Texture* m_pText;

	// Managers
	StateMachine* pFSM;
	AudioManager* pAM;

	Game() { cout << "Constructing game..." << '\n'; }
public:
	~Game() {
		delete pFSM;
		delete pAM;
	}

	// Global instance
	static Game* Instance() {
		static Game* instance = new Game();
		return instance;
	}


	// Getters.
	SDL_Renderer* GetRenderer() { return m_pRenderer; }
	SDL_Texture* GetTexture() { return m_pText; }
	StateMachine* GetFSM() { return pFSM; }
	AudioManager* GetAM() { return pAM; }
	int GetMouseX() { return m_iMouseX; }
	int GetMouseY() { return m_iMouseY; }
	int GetLeftMouse() { return m_bLeftMouse; }
	void DoQuit() { m_bRunning = false; }


	// Key check
	bool KeyDown(SDL_Scancode c);


	// Game Initialization
	bool Init(const char* title, int xpos, int ypos, int width,	int height, int flags);


	// Returns running bool
	bool Running() {
		return m_bRunning;
	}


	// Game Tick
	bool Tick();


	// Call StateMachine's Update
	void Update() {
		GetFSM()->Update();
	}


	// SDL HandleEvents
	void HandleEvents();


	// Call StateMachine's Render
	void Render(){
		GetFSM()->Render();
	}


	void Clean();
};
