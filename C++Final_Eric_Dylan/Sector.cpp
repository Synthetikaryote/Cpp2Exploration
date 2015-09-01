#include "Sector.h"
#include "Uber.h"
Sector::Sector(int seed)
{
	srand(seed);
	Uber &uber = Uber::getInstance();
	mSprite = new Sprite(uber.sectorWidth, uber.sectorHeight);

	for(int i = 0; i < uber.sectorWidth; ++i)
	{
		for(int j = 0; j < uber.sectorHeight; ++j)
		{
			int spawn = rand() % 100;
			
			mSprite->data[i * uber.sectorWidth + j].Attributes = 0x08;

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

}


Sector::~Sector()
{
	delete mSprite;
}