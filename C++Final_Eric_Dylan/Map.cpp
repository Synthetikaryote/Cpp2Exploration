#include "Map.h"
#include <iostream>
#include "Uber.h"
#include <memory>

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
				shared_ptr<Sector> newSector(new Sector (1, x+X, y+Y));
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

CHAR_INFO* Map::at(int x, int y) {
	shared_ptr<Sector> sector = findSectorAt(x, y);
	if (sector != nullptr) {
		Uber& uber = Uber::getInstance();
		int w = uber.sectorWidth;
		int h = uber.sectorHeight;
		// make sure negative modulus becomes positive
		// http://stackoverflow.com/questions/13794171/how-to-make-the-mod-of-a-negative-number-to-be-positive
		int c = ((x % w) + w) % w;
		int r = ((y % h) + h) % h;
		return &sector->mSprite->data[r * w + c];
	}
	return nullptr;
}

shared_ptr<Sector> Map::findSectorAt(int x, int y) {
	Uber& uber = Uber::getInstance();
	int w = uber.sectorWidth;
	int h = uber.sectorHeight;
	int sectorX = floorf(static_cast<float>(x) / w) + (x + viewX) / w;
	int sectorY = floorf(static_cast<float>(y) / h) + (y + viewY) / h;
	for (auto sector : mSectors)
		if (sectorX == sector->mlocX && sectorY == sector->mlocY)
			return sector;
	return nullptr;
}