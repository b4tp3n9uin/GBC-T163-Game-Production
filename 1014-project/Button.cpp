#include "Button.h"
#include "FSM.h"
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"

Button::Button(const char* s, SDL_Rect d){

	// Load button picture
	m_pSurf = IMG_Load(s);
	// Create texture
	m_pText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), m_pSurf);
	// Delete surface
	SDL_FreeSurface(m_pSurf);

	m_bReleased = true;
	m_rDst = d;
	m_rSrc.x = m_rSrc.y = 0;
	m_rSrc.w = m_rDst.w;
	m_rSrc.h = m_rDst.h;
}

Button::~Button(){
	SDL_DestroyTexture(m_pText);
}


void Button::Update(){
	// Get mouse X and Y
	int mx = Game::Instance()->GetMouseX();
	int my = Game::Instance()->GetMouseY();

	// If mouse is inside button
	if (mx < (m_rDst.x + m_rDst.w) && mx > m_rDst.x && my < (m_rDst.y + m_rDst.h) && my > m_rDst.y){
		if (Game::Instance()->GetLeftMouse() && m_bReleased){
			m_iFrame = MOUSE_DOWN; // 2
			m_bReleased = false;
		}
	}else{
		m_iFrame = MOUSE_UP;  // 0
	}
}


void Button::Render(){
	m_rSrc.x = m_rDst.w * m_iFrame;
	SDL_RenderCopy(Game::Instance()->GetRenderer(), m_pText, &m_rSrc, &m_rDst);
}
