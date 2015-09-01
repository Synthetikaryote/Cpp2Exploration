#include "Map.h"
#include <iostream>

#define max(a,b)            (((a) > (b)) ? (a) : (b))

Map::Map()
{
	Sector* newSector = new Sector(1234,0,0);
	mSectors.push_back(newSector);
	//newSector = new Sector(4312,1,0);
	//mSectors.push_back(newSector);
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
				newMap.push_back(new Sector(123456, x + X, y + Y));
			}
        }
        if( (x == y) || ((x < 0) && (x == -y)) || ((x > 0) && (x == 1-y))){
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