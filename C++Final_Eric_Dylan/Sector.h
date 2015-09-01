#pragma once

#include <Windows.h>
#include "Sprite.h"

class Sector
{
public:
	Sector(int seed, int locX, int locY);
	~Sector();

	int mlocX, mlocY;

	Sprite* mSprite;
};

