#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Button.h"
#include "Player.h"
#include "EnemyManager.h"
using namespace std;
class Explosion;
class Items;
// Abstract class for all states
class State {
protected:
	State() {}
public:
	virtual void Update() = 0;
	virtual void Render();
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Resume() = 0;
};





// TitleState
class TitleState : public State {
private:
	// Logo
	SDL_Rect srcR, destR;
	SDL_Surface* LogoSurf;
	SDL_Texture* LogoText;

	// Background
	SDL_Surface* bgSurf;
	SDL_Texture* bgText;

	// Button vector
	vector<Button*> m_vButtons;

public:
	TitleState() {}
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume() {}

	// Buttons
	enum btn { play, quit, score };
};


// GameState
class GameState : public State {
public:
	GameState() {}
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << '\n'; }

	// Sound effects
	enum sfx { fire, hit, pew, powerup1, powerup2 };

	// Background
	SDL_Surface* bgSurf;
	SDL_Texture* bgText;
	SDL_Rect bgRect;

	// Checks if your still paying the game
	bool ingame;

	// Player is dead bool
	bool isDead;

	// Player object
	Player* p;

	// EnemyManager
	EnemyManager* eManger;

	// Firing flag
	bool canFire = true;
	bool canBomb = true;
	bool canBombDamage = true;
	// timeCheck
	float timer;
	float bulletTimer;
	float limitBulletTime;
	// Score board
	int score;
	TTF_Font* scoreFont;
	SDL_Color scoreColor = {255,255,255,255};
	SDL_Surface* scoreSurf;
	SDL_Texture* scoreText;
	SDL_Rect sRect;
	string buff;
	const char* currScore;

	// bomb board
	SDL_Surface* bombSurf;
	SDL_Texture* bombText;
	SDL_Rect bRect;

	// CollisionCheck
	bool CollisionCheck(SDL_Rect a, SDL_Rect b);

	// Explosion vector
	vector<Explosion*> vExplosion;
	// Item vector
	vector<Items*> vItems;

};


// PauseState
class PauseState : public State {
public:
	PauseState() {}
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume() {}

	// Message and title in PauseState
	TTF_Font* gameFont;
	SDL_Color fontColor;
	SDL_Color fontColor2;
	SDL_Surface* message;
	SDL_Surface* message2;
	SDL_Texture* pauseMessage;
	SDL_Texture* pauseMessage2;
	SDL_Rect Mdest;
	SDL_Rect Mdest2;


};


// InstructionsState
class InstructionState : public State
{
public:
	vector<Button*> iButtons;
	InstructionState() {}
	void Enter();
	void Update();
	void Render();
	void Exit();
	void Resume() {}

	// Exit Button
	enum ibtn { menu };

	// Background
	SDL_Surface* bgSurf;
	SDL_Texture* bgText;
};


// LoseState
class LoseState : public State {
public:
	vector<Button*> lButtons;
	LoseState(){}
	void Enter();
	void Update();
	void Render();
	void Exit();
	void Resume() {}
	// Buttons
	enum lbtn { menu };
	enum lsfx { death };

	// Logo
	SDL_Rect LsrcR, LdestR;
	SDL_Surface* LostSurf;
	SDL_Texture* LostText;

	// Background
	SDL_Surface* bgSurf;
	SDL_Texture* bgText;
};






class StateMachine{
private:
	vector<State*> m_vStates;
public:
	void Update();
	void Render();
	void PushState(State* pState);
	void ChangeState(State* pState);
	void PopState();
	void Clean();

	// State vector getter
	vector<State*>& GetStates() {
		return m_vStates;
	}

};
