#pragma once
#include <chrono>
#include <cmath>
#include <iostream>
#include <time.h>
using namespace std;
using namespace chrono;

class SDL_Timer
{
	static bool m_bGotTick;
	static unsigned int m_OldTick;
	static unsigned int m_CurrentTick;

	friend class SDL_GameStateManager;
	static void UpdateTimer();

public:
	static bool Tick();
	static float GetDT();
	static unsigned int GetCT() { return m_CurrentTick; };
};