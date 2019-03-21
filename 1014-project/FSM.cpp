#include "FSM.h"
#include "Game.h"
#include <fstream>
#include <string>
#include "Bullet.h"
#include "Explosion.h"
using namespace std;

void State::Render(){
	SDL_RenderPresent(Game::Instance()->GetRenderer());
}







// Title State
void TitleState::Enter(){
	cout << "Entering Title..." << '\n';

	// Load the Logo
	// LogoSurf = IMG_Load("img/Title2.png");
	// LogoText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), LogoSurf);

	// Load the background
	bgSurf = IMG_Load("img/StartScreen.png");
	bgText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), bgSurf);

	// Load the buttons
	m_vButtons.push_back(new Button("img/new-game.png", { 125,600,200,60 }));
	m_vButtons.push_back(new Button("img/exit.png", { 700,600,122,60 }));
	m_vButtons.push_back(new Button("img/score-board.png", { 405,600,214,60 }));

	// Load and play menu music
	Game::Instance()->GetAM()->LoadMusic("aud/Double_the_Bits.mp3");
	Game::Instance()->GetAM()->PlayMusic();
}

void TitleState::Update(){
	// Logo size and position
	destR.h = 83;
	destR.w = 714;
	destR.x = 155;
	destR.y = 200;

	// Button Update
	for (int i = 0; i < (int)m_vButtons.size(); i++){
		m_vButtons[i]->Update();
	}

	// Button event
	if (m_vButtons[btn::play]->Clicked()){
		Game::Instance()->GetFSM()->ChangeState(new GameState());
	}else if (m_vButtons[btn::quit]->Clicked()){
		Game::Instance()->DoQuit();
	}else if ((m_vButtons[btn::score]->Clicked())) {
		// Game::Instance()->GetFSM()->ChangeState(new ScoreBoardState());
	}
}

void TitleState::Render(){
	// Set background to white
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Game::Instance()->GetRenderer());

	// Renders the background
	SDL_RenderCopy(Game::Instance()->GetRenderer(), bgText, NULL, NULL);

	// Renders the title logo
	SDL_RenderCopy(Game::Instance()->GetRenderer(), LogoText, NULL, &destR);

	// Renders all the buttons
	for (int i = 0; i < (int)m_vButtons.size(); i++){
		m_vButtons[i]->Render();
	}

  // SDL_RenderPresent
	State::Render();
}

void TitleState::Exit(){
	cout << "Exiting Title..." << '\n';

	// Clear all music and sfx
	Game::Instance()->GetAM()->ClearMusic();
	Game::Instance()->GetAM()->ClearSounds();

	// Deallocate all buttons and delete vector
	for (int i = 0; i < (int)m_vButtons.size(); i++){
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}

	// Clean out title logo
	SDL_FreeSurface(LogoSurf);
	SDL_DestroyTexture(LogoText);

	// Clean out background
	SDL_FreeSurface(bgSurf);
	SDL_DestroyTexture(bgText);

	// Clean out all buttons
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}
























// Game State
bool GameState::CollisionCheck(SDL_Rect a, SDL_Rect b){
  bool collision = false;
  if ((a.x < b.x + b.w) && (a.x + a.w > b.x) && (a.y + a.h > b.y) && (a.y < b.y + b.h)){
    collision = true;
  }
  return collision;
}



void GameState::Enter(){
	cout << "Entering Game..." << '\n';

	// Ingame bool used to stop CollisionCheck
	ingame = true;
	isDead = false;

	// Load all music and sfx
	Game::Instance()->GetAM()->LoadMusic("aud/Rubik.mp3");
	Game::Instance()->GetAM()->LoadSound("aud/Fire.wav");
	Game::Instance()->GetAM()->LoadSound("aud/Hit.wav");
	Game::Instance()->GetAM()->LoadSound("aud/pew.wav");
	Game::Instance()->GetAM()->LoadSound("aud/powerup1.wav");
	Game::Instance()->GetAM()->LoadSound("aud/powerup2.wav");
	Game::Instance()->GetAM()->PlayMusic();


	// Load background
	bgRect.x = 0;
	bgRect.y = 0;
	bgSurf = IMG_Load("img/Background.png");
	bgText = SDL_CreateTextureFromSurface(Game::Instance() -> GetRenderer(), bgSurf);


	// Initialize the player
	p = new Player(50, 300);
	p -> pSpeed = 4;
	p -> bulletCount = 0;
	p -> pSurf = IMG_Load("img/Player.png");
	p -> pText = SDL_CreateTextureFromSurface(Game::Instance() -> GetRenderer(), p -> pSurf);


	// Load score board
	sRect.x = 484;
	sRect.y = 0;
	scoreFont = TTF_OpenFont("img/scorebFont.ttf", 20);
	score = 0;


	// Initialize EnemyManager
	eManger = new EnemyManager();

}



void GameState::Update(){
	// Quit game if player is dead
	if (isDead) {
		// Dead
		Game::Instance()->GetFSM()->ChangeState(new LoseState());

		// Turn ingame flag to false prevent CollisionCheck after exiting
		ingame = false;

	}else{

		// Clear score cache
		SDL_DestroyTexture(scoreText);
		SDL_FreeSurface(scoreSurf);

		// Update score board according to the score int
		scoreSurf = TTF_RenderText_Solid( scoreFont, to_string(score).c_str(), scoreColor);
		scoreText = SDL_CreateTextureFromSurface(Game::Instance() -> GetRenderer(), scoreSurf);


		// Update Player
		p -> Update();


		// Update EnemyManager
		eManger -> Update();


		// Update score board
		sRect.w = 75;
		sRect.h = 50;

		// Update background
		bgRect.w = 2048;
		bgRect.h = 769;

		// if reached the end of the background Rect, reload it
		if (bgRect.x < -1024){
			bgRect.x = 0;
		}else{
			// else move the background towards left
			bgRect.x -= 1;
		}



		// Pause & Title
		if (Game::Instance()->KeyDown(SDL_SCANCODE_P) == 1){
			// Press "P" to go into PauseState
			Game::Instance()->GetFSM()->PushState(new PauseState());
		}else if (Game::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1){
			// Press "Esc" to go into TitleState
			Game::Instance()->GetFSM()->ChangeState(new TitleState());
			// Turn ingame flag to false prevent CollisionCheck after exiting
			ingame = false;
		}



		// Player movement
		if (Game::Instance()->KeyDown(SDL_SCANCODE_W) == 1 && p -> pDestR.y >= 0) {
			p->pDestR.y -= p->pSpeed;
		}else if (Game::Instance()->KeyDown(SDL_SCANCODE_S) == 1 && p -> pDestR.y <= 700) {
			p->pDestR.y += p->pSpeed;
		}



		// Player firing
		if (Game::Instance()->KeyDown(SDL_SCANCODE_SPACE) == 1 && canFire) {

			// Play fire sound effect
			Game::Instance()->GetAM()->PlaySound(sfx::pew);

			// Spawn bullet
			p -> SpawnBullet();


			// flag to false
			canFire = false;

		}else if (Game::Instance()->KeyDown(SDL_SCANCODE_SPACE) == 0) {
			// If key up turn flag to true
			canFire = true;
		}


		// Update all explosion
		for (int i = 0; i < vExplosion.size(); i++) {
			vExplosion[i] -> Update();
		}

		if (ingame) {

			// Collision between enemy and player
			for (int i = 0; i < eManger -> GetEnemies().size(); i++) {
				if (CollisionCheck(eManger -> GetEnemies()[i] -> eDestR, p -> pDestR)) {
					isDead = true;
				}
			}

			// Player Bullet Collision with enemy
			for (int b = 0; b < p -> GetBullets().size(); b++) {
				for (int e = 0; e < eManger -> GetEnemies().size(); e++) {
					// If bullet collide with enemy
					if (CollisionCheck(p -> GetBullets()[b] -> bDestR, eManger -> GetEnemies()[e] -> eDestR)) {

						// Delete the bullet
						p -> GetBullets()[b] = nullptr;
						p -> GetBullets().erase(p -> GetBullets().begin() + b);

						// Create explosion
						vExplosion.push_back(new Explosion(eManger -> GetEnemies()[e] -> eDestR.x, eManger -> GetEnemies()[e] -> eDestR.y));


						if (eManger -> GetEnemies()[e] -> Etype == 0) {
							score += 10;
						}else if (eManger -> GetEnemies()[e] -> Etype == 1) {
							score += 20;
						}else if (eManger -> GetEnemies()[e] -> Etype == 2) {
							score += 25;
						}


						// Play explosion sfx
						Game::Instance()->GetAM()->PlaySound(sfx::hit);

						// Delete the enemy
						eManger -> GetEnemies()[e] = nullptr;
						eManger -> GetEnemies().erase(eManger -> GetEnemies().begin() + e);
						break;
					}
				}
			}
			p -> GetBullets().shrink_to_fit();
			eManger -> GetEnemies().shrink_to_fit();
		}
	}
}


void GameState::Render(){
	// Bottom color set to black
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Game::Instance()->GetRenderer());

	// Render background image
	SDL_RenderCopy(Game::Instance()->GetRenderer(), bgText, NULL, &bgRect);

	// Call player Render
	p -> Render();

	// Call EnemyManager Render
	eManger -> Render();

	// Render all Explosion
	for (int i = 0; i < vExplosion.size(); i++) {
		vExplosion[i] -> Render();
	}


	// Render score board
	SDL_RenderCopy(Game::Instance()->GetRenderer(), scoreText, NULL, &sRect);


	// SDL_RenderPresent
	State::Render();
}

void GameState::Exit(){
	cout << "Exiting Game..." << '\n';

	// Delete background
	SDL_FreeSurface(bgSurf);
	SDL_DestroyTexture(bgText);

	// Delete Score board
	TTF_CloseFont(scoreFont);
	SDL_FreeSurface(scoreSurf);
	SDL_DestroyTexture(scoreText);

	// Clean explosion
	for (int i = 0; i < vExplosion.size(); i++) {
		vExplosion[i] -> Clean();
	}

	// Call EnemyManager clean
	eManger -> Clean();

	// Call player clean
	p -> Clean();

	// Clear all the music
	Game::Instance()->GetAM()->ClearMusic();
	Game::Instance()->GetAM()->ClearSounds();
}











// Pause State
void PauseState::Enter(){
	cout << "Entering Pause..." << '\n';

	// Pause music
	Game::Instance()->GetAM()->ToggleMusic();

	// Load pause screen message
	gameFont = TTF_OpenFont("img/gamefont.ttf", 20); // 8bit font
	fontColor = {255,255,255,255}; // white
	message = TTF_RenderText_Solid( gameFont, "Press \'R\' to Go Back to Game", fontColor);
	pauseMessage = SDL_CreateTextureFromSurface(Game::Instance() -> GetRenderer(), message);

	// Load pause screen title
	fontColor2 = {255, 0, 77, 255}; // pink
	message2 = TTF_RenderText_Solid( gameFont, "Paused", fontColor2);
	pauseMessage2 = SDL_CreateTextureFromSurface(Game::Instance() -> GetRenderer(), message2);

}

void PauseState::Update(){
	// Update the pause message
	Mdest.h = 50;
	Mdest.w = 700;
	Mdest.x = 162;
	Mdest.y = 312;

	// Update the pause title
	Mdest2.h = 150;
	Mdest2.w = 500;
	Mdest2.x = 262;
	Mdest2.y = 150;

	// Press "R" to exite Pause State
	if (Game::Instance()->KeyDown(SDL_SCANCODE_R) == 1){
		Game::Instance()->GetFSM()->PopState();
	}
}

void PauseState::Render(){
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 40, 40, 40, 255);
	SDL_RenderClear(Game::Instance()->GetRenderer());

	// Render the pause screen message "Press r to go back to game"
	SDL_RenderCopy(Game::Instance()->GetRenderer(), pauseMessage, NULL, &Mdest);

	// Render the pause title
	SDL_RenderCopy(Game::Instance()->GetRenderer(), pauseMessage2, NULL, &Mdest2);


	State::Render();
}

void PauseState::Exit(){
	cout << "Exiting Pause..." << '\n';

	// Delete texture, surface and font
	SDL_DestroyTexture(pauseMessage);
	SDL_DestroyTexture(pauseMessage2);
	SDL_FreeSurface(message);
	SDL_FreeSurface(message2);
	TTF_CloseFont(gameFont);

	// ToggleMusic
	Game::Instance()->GetAM()->ToggleMusic();
}














// LoseState
void LoseState::Enter(){
	cout << "Entering LoseState..." << '\n';

	// Load death sound and play it
	Game::Instance()->GetAM()->LoadSound("aud/death.wav");
	Game::Instance()->GetAM()->PlaySound(lsfx::death);

	// Load button
	lButtons.push_back(new Button("img/main-menu.png", { 409,450,205,60 }));

	// Load the Logo
	LostSurf = IMG_Load("img/Game-Over.png");
	LostText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), LostSurf);

}


void LoseState::Update(){
	// Logo size and position
	LdestR.h = 66;
	LdestR.w = 487;
	LdestR.x = 269;
	LdestR.y = 251;

	// Button Update
	for (int i = 0; i < (int)lButtons.size(); i++){
		lButtons[i]->Update();
	}

	// Button event
	if (lButtons[lbtn::menu]->Clicked()){
		Game::Instance()->GetFSM()->ChangeState(new TitleState());
	}
}

void LoseState::Render(){
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Game::Instance()->GetRenderer());

	// Logo
	SDL_RenderCopy(Game::Instance()->GetRenderer(), LostText, NULL, &LdestR);

	// Renders all the buttons
	for (int i = 0; i < (int)lButtons.size(); i++){
		lButtons[i]->Render();
	}

	State::Render();
}



void LoseState::Exit(){
	cout << "Exiting LoseState..." << '\n';

}
















// StateMachine
void StateMachine::Update(){
	if (!m_vStates.empty()){
		m_vStates.back()->Update();
	}
}

void StateMachine::Render(){
	if (!m_vStates.empty())
		m_vStates.back()->Render();
}

void StateMachine::PushState(State* pState){
	m_vStates.push_back(pState);
	m_vStates.back()->Enter();
}

void StateMachine::ChangeState(State* pState){
	if (!m_vStates.empty()){
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	pState->Enter();
	m_vStates.push_back(pState);
}

void StateMachine::PopState(){
	if (!m_vStates.empty()){
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	m_vStates.back()->Resume();
}

void StateMachine::Clean(){
	while (!m_vStates.empty()){
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
}
