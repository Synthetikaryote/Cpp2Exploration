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
			
			mSprite->data[j * uber.sectorWidth + i].Attributes = 0x2F;

			if (spawn < 1 && i >= uber.tree.w && j >= uber.tree.h)
			{
				uber.tree.x = i - uber.tree.w + 1;
				uber.tree.y = j - uber.tree.h + 1;
				uber.tree.Draw(mSprite->data, uber.sectorWidth, uber.sectorHeight);
			}
			else
			{
				mSprite->data[j * uber.sectorWidth + i].Char.AsciiChar = ' ';
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

