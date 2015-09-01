#include "Sector.h"
#include "Uber.h"
#include <sstream>
#include <string>

Sector::Sector(int seed, int locX, int locY)
{
	string seedKey;
	stringstream strs;
	strs << seed << locX << locY;
	seedKey = strs.str();



	srand(stoi(seedKey));

	Uber &uber = Uber::getInstance();
	mSprite = new Sprite(uber.sectorWidth, uber.sectorHeight);

	for(int i = 0; i < uber.sectorWidth; ++i)
	{
		for(int j = 0; j < uber.sectorHeight; ++j)
		{
			int spawn = rand() % 100;
			
			mSprite->data[i * uber.sectorWidth + j].Attributes = 0x2F;

			if(spawn < 10)
			{
				mSprite->data[i * uber.sectorWidth + j].Char.AsciiChar = 't';
			}
			else
			{
				mSprite->data[i * uber.sectorWidth + j].Char.AsciiChar = ' ';
			}
		}
	}
	mlocX = locX;
	mlocY = locY;
	mSprite->x = locX * 64;
	mSprite->y = locY * 64;
}


Sector::~Sector()
{
	delete mSprite;
}

