#pragma once

#include <Windows.h>
#include "Sprite.h"

class Sector
{
public:
	Sector(unsigned int seed, int locX, int locY, bool spawnApple = true);
	~Sector();
	void Generate(unsigned int seed, bool spawnApple = true);

	int mlocX, mlocY;
	bool built = false;
	Sprite* mSprite;

	unsigned int mSeed = 0;
};

