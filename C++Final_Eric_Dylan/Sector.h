#pragma once

#include <Windows.h>
#include "Sprite.h"

class Sector
{
public:
	Sector(int seed, int locX, int locY);
	~Sector();
	void Generate(int seed, int locX, int locY);

	int mlocX, mlocY;
	bool built = false;
	Sprite* mSprite;
};

