#include "Map.h"
#include <iostream>
#include "Uber.h"

#define max(a,b)            (((a) > (b)) ? (a) : (b))

Map::Map()
{
}


Map::~Map()
{
	for (Sector* sector : mSectors) {
		delete sector;
	}
	mSectors.clear();
}

void Map::Update(float elapsed) {
	int sectorX = -viewX / 64;
	int sectorY = -viewY / 64;

	Spiral( sectorX, sectorY, 3, 3);
	
	for (Sector* sector : mSectors) {
		sector->mSprite->x = viewX + (sector->mlocX * sector->mSprite->w);
		sector->mSprite->y = viewY + (sector->mlocY * sector->mSprite->h);
	}
}

void Map::Draw(CHAR_INFO* buffer, int bufferWidth, int bufferHight) {	
	for (Sector* sector : mSectors) {
		sector->mSprite->Draw(buffer, bufferWidth, bufferHight);
	}
}

void Map::Spiral( int X, int Y, int sizeX, int sizeY){
	bool loaded = false;
	vector<Sector*> newMap;
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
					std::vector<Sector*>::iterator it = mSectors.begin() + i;
					mSectors.erase(it);
					loaded = true;
					break;
				}
			}
			if(!loaded)
			{
				newMap.push_back(new Sector(1, x + X, y + Y));
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
	for(Sector* sector : mSectors)
	{
		delete sector;
	}
	mSectors = newMap;
}

CHAR_INFO Map::at(int x, int y) {
	Uber& uber = Uber::getInstance();
	int w = uber.sectorWidth;
	int h = uber.sectorHeight;
	int macroX = floorf(static_cast<float>(x) / w) + (x + viewX) / w;
	int macroY = floorf(static_cast<float>(y) / h) + (y + viewY) / h;
	for (Sector* sector : mSectors) {
		if (macroX == sector->mlocX && macroY == sector->mlocY) {
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