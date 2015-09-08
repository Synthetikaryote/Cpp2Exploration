#include "Sector.h"
#include "Uber.h"
#include <sstream>
#include <string>
#include <thread>

Sector::Sector(unsigned int seed, int locX, int locY, bool spawnApple)
{
	mlocX = locX;
	mlocY = locY;
	mSeed = seed;
	thread t(&Sector::Generate, this, seed, spawnApple);
	t.join();
}


Sector::~Sector()
{
	delete mSprite;
}

void Sector::Generate(unsigned int seed, bool spawnApple)
{
	srand(seed);

	Uber &uber = Uber::getInstance();
	mSprite = new Sprite(uber.sectorWidth, uber.sectorHeight);

	for(int i = 0; i < uber.sectorWidth; ++i)
	{
		for(int j = 0; j < uber.sectorHeight; ++j)
		{
			int spawn = rand() % 1000;
			
			mSprite->data[j * uber.sectorWidth + i].Attributes = 0x2F;

			if (spawn < 11 && i >= uber.tree.w && j >= uber.tree.h)
			{
				uber.tree.x = i - uber.tree.w + 1;
				uber.tree.y = j - uber.tree.h + 1;
				uber.tree.Draw(mSprite->data, uber.sectorWidth, uber.sectorHeight);
			}
			else if(spawn < 1)
			{
				//apples
				if(spawnApple)
				{
					mSprite->data[j * uber.sectorWidth + i].Attributes = 0x2C;
					mSprite->data[j * uber.sectorWidth + i].Char.AsciiChar = 235;
					spawnApple = false;
				}
				else
				{
					mSprite->data[j * uber.sectorWidth + i].Char.AsciiChar = ' ';
				}
			}
			else
			{
				mSprite->data[j * uber.sectorWidth + i].Char.AsciiChar = ' ';
			}
		}
	}
	mSprite->x = mlocX * 64;
	mSprite->y = mlocY * 64;
	built = true;
}

