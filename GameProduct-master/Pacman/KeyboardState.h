#pragma once

#include <map>
#include <vector>
#include "KeyState.h"

enum class Keys
{
	RETURN = '\r',
	ESCAPE = '\033',
	SPACE = ' ',
	b = 'b',
	w = 'w',
	s = 's',
};

class KeyboardState
{
	friend class Keyboard;
	std::map<Keys, KeyState> m_KeyData;

public:
	bool IsKeyDown(Keys key);
};
