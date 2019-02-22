#include "SDL_Timer.h"

#include <SDL.h>

bool SDL_Timer::m_bGotTick;
unsigned int SDL_Timer::m_OldTick;
unsigned int SDL_Timer::m_CurrentTick;

void SDL_Timer::UpdateTimer()
{
	m_OldTick = m_CurrentTick;
	m_CurrentTick = SDL_GetTicks();
}

float SDL_Timer::GetDT()
{/*-*/

	float res = (m_CurrentTick - m_OldTick) / 1000.0f;

	if (res > 0.2f)
		res = 0.2f;

	return res;
}
bool SDL_Timer::Tick()
{
	auto duration = steady_clock::now().time_since_epoch();
	auto count = duration_cast<microseconds>(duration).count();
	int tick = 1000000 / 60;

	if (count % tick == 0) // Drops potential duplicate frames.
	{
		if (m_bGotTick == false)
		{
			m_bGotTick = true;
			//cout << "Tick " << tick << " @ " << count << endl;
			return true;
		}
		return false;
	}
	else m_bGotTick = false;
	return false;
}