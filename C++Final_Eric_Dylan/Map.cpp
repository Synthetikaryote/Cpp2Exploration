#include "Map.h"
#include <iostream>
#include "Uber.h"
#include <memory>
#include <sstream>
#include <string>

using namespace std;

Map::Map()
{
}


Map::~Map()
{
	//for (auto sector : mSectors) {
	//	delete sector;
	//}
	mSectors.clear();
}

void Map::Update(float elapsed) {
	int sectorX = -viewX / 64;
	int sectorY = -viewY / 64;

	Spiral( sectorX, sectorY, 3, 3);
	
	for (auto sector : mSectors) {
		sector->mSprite->x = viewX + (sector->mlocX * sector->mSprite->w);
		sector->mSprite->y = viewY + (sector->mlocY * sector->mSprite->h);
	}
}

void Map::Draw(CHAR_INFO* buffer, int bufferWidth, int bufferHight) {	
	for (auto sector : mSectors) {
		sector->mSprite->Draw(buffer, bufferWidth, bufferHight);
	}
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

void Map::Spiral( int X, int Y, int sizeX, int sizeY){
	bool loaded = false;
	vector<shared_ptr<Sector>> newMap;
    int x,y,dx,dy;
    x = y = dx =0;
    dy = -1;
    int t = max(sizeX,sizeY);
    int maxI = t*t;
    for(int i =0; i < maxI; i++){
		loaded = false;
        if ((-sizeX/2 <= x) && (x <= sizeX/2) && (-sizeY/2 <= y) && (y <= sizeY/2)){
			for(unsigned int i = 0; i < mSectors.size(); ++i)
			{
				if(mSectors[i]->mlocX == x + X && mSectors[i]->mlocY == y+Y)
				{
					newMap.push_back(mSectors[i]);
					std::vector<shared_ptr<Sector>>::iterator it = mSectors.begin() + i;
					mSectors.erase(it);
					loaded = true;
					break;
				}
			}

			if(!loaded)
			{
				string seedKey;
				stringstream strs;
				strs << 1 << x+X << y+Y;
				seedKey = strs.str();
				unsigned int seed = myhash(seedKey);
				bool spawnApple = true;
				
				for(auto apple : applesCollected)
				{
					if(apple == seed)
					{
						spawnApple = false;
						break;
					}
				}

				shared_ptr<Sector> newSector(new Sector (seed, x+X, y+Y, spawnApple));

				newMap.push_back(newSector);
			}
        }
        if((x == y) || ((x < 0) && (x == -y)) || ((x > 0) && (x == 1-y))){
            t = dx;
            dx = -dy;
            dy = t;
        }
        x += dx;
        y += dy;
    }
	for(unsigned int i = 0; i < mSectors.size(); ++i)
	{
		mSectors.pop_back();
	}
	mSectors = newMap;
}

CHAR_INFO Map::at(int x, int y) {
	Uber& uber = Uber::getInstance();
	int w = uber.sectorWidth;
	int h = uber.sectorHeight;
	int sectorX, sectorY;
	worldXYToSectorXY(x, y, sectorX, sectorY);
	for (auto sector : mSectors) {
		if (sectorX == sector->mlocX && sectorY == sector->mlocY) {
			// make sure negative modulus becomes positive
			// http://stackoverflow.com/questions/13794171/how-to-make-the-mod-of-a-negative-number-to-be-positive
			int c = ((x % w) + w) % w;
			int r = ((y % h) + h) % h;
			return sector->mSprite->data[r * w + c];
		}
	}
	CHAR_INFO blank;
	blank.Char.AsciiChar = 0;
	return blank;
}

void Map::worldXYToSectorXY(int x, int y, int& sectorX, int& sectorY) {
	Uber& uber = Uber::getInstance();
	int w = uber.sectorWidth;
	int h = uber.sectorHeight;
	sectorX = floorf(static_cast<float>(x) / w) + (x + viewX) / w;
	sectorY = floorf(static_cast<float>(y) / h) + (y + viewY) / h;
}