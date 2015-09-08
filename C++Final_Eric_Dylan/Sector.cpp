#include "Sector.h"
#include "Uber.h"
#include <sstream>
#include <string>
#include <thread>

Sector::Sector(int seed, int locX, int locY)
{
	thread t(&Sector::Generate, this, seed, locX, locY);
	t.join();
}


Sector::~Sector()
{
	delete mSprite;
}

static const size_t InitialFNV = 2166136261U;
static const size_t FNVMultiple = 16777619;
/* Fowler / Noll / Vo (FNV) Hash */
size_t myhash(const string &s)
{
    size_t hash = InitialFNV;
    for(size_t i = 0; i < s.length(); i++)
    {
        hash = hash ^ (s[i]);       /* xor  the low 8 bits */
        hash = hash * FNVMultiple;  /* multiply by the magic number */
    }
    return hash;
}

void Sector::Generate(int seed, int locX, int locY)
{
	bool appleSpawned = false;
	string seedKey;
	stringstream strs;
	strs << seed << locX << locY;
	seedKey = strs.str();



	srand(myhash(seedKey));



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
				if(appleSpawned)
				{
					mSprite->data[j * uber.sectorWidth + i].Char.AsciiChar = ' ';
				}
				else
				{
					mSprite->data[j * uber.sectorWidth + i].Attributes = 0x2C;
					mSprite->data[j * uber.sectorWidth + i].Char.AsciiChar = 235;
					appleSpawned = true;
				}
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
	built = true;
}

