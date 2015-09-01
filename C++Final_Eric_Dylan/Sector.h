#pragma once

#include <Windows.h>
#include "Sprite.h"

class Sector
{
public:
	Sector(int seed);
	~Sector();

	Sprite* mSprite;
};

