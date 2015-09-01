#include "Sector.h"
#include "Uber.h"
Sector::Sector(int seed)
{
	srand(seed);
	mSprite = new Sprite(64,64);
	Uber &uber = Uber::getInstance();

	for(unsigned int i = 0; i < uber.sectorHeight; ++i)
	{
		for(unsigned int j = 0; j < uber.sectorWidth; ++j)
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