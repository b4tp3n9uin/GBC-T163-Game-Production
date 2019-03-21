#include "Player.h"
#include "Game.h"
#include "Bullet.h"
using namespace std;


void Player::SpawnBullet(){
  // Push a new bullet obj into the bullet vector
	m_vBullets.push_back(new Bullet(pLocation.x + 30, pLocation.y + 20));
}






// This will be called in GameState's Render function
void Player::Update(){


  // Update the player size
  pDestR.h = 64;
	pDestR.w = 64;

  // Update Player location according to its movement
  pLocation.x = pDestR.x;
  pLocation.y = pDestR.y;

  // Determine the numbers of bullets on the screen
  bulletCount = m_vBullets.size();

	// Update all bullet
  for (int i = 0; i < m_vBullets.size(); i++){
    m_vBullets[i]->Update();
		// Delete bullet if it fly out of the screen
    if (m_vBullets[i]->bDestR.x < 0 || m_vBullets[i]->bDestR.x > 1024 ||
      m_vBullets[i]->bDestR.y < 0 || m_vBullets[i]->bDestR.y > 768){
			m_vBullets[i]->Clean();
			delete m_vBullets[i];
      m_vBullets[i] = nullptr;
      m_vBullets.erase(m_vBullets.begin() + i);
    }
  }
  m_vBullets.shrink_to_fit();
}





// This will be called in GameState's Render function
void Player::Render(){

  // Render Player graphics
	SDL_RenderCopy(Game::Instance()->GetRenderer(), pText, NULL, &pDestR);

	// Render bullet
	for (int i = 0; i < m_vBullets.size(); i++){
		m_vBullets[i] -> Render();
	}
}




void Player::Clean(){
	// Delete all bullets
	for (int i = 0; i < m_vBullets.size(); i++){
		delete m_vBullets[i];
		m_vBullets[i] = nullptr;
	}
	m_vBullets.clear();
	m_vBullets.shrink_to_fit();

	// Delete player graphics
	SDL_FreeSurface(pSurf);
	SDL_DestroyTexture(pText);
}
