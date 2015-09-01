#include "Map.h"

Map::Map()
{
	Sector* newSector = new Sector(1234);
	newSector->mSprite->x = 0;
	newSector->mSprite->y = 0;
	newSector->locX = 0;
	newSector->locY = 0;
	mSectors.push_back(newSector);
	newSector = new Sector(4312);
	newSector->mSprite->x = 64;
	newSector->mSprite->y = 0;
	newSector->locX = 1;
	newSector->locY = 0;
	mSectors.push_back(newSector);
}


Map::~Map()
{
	for (Sector* sector : mSectors) {
		delete sector;
	}
	mSectors.clear();
}

void Map::Update(float elapsed) {
	for (Sector* sector : mSectors) {
		sector->mSprite->x = viewX + (sector->locX * sector->mSprite->w);
		sector->mSprite->y = viewY + (sector->locY * sector->mSprite->h);
	}
}

void Map::Draw(CHAR_INFO* buffer, int bufferWidth, int bufferHight) {	
	for (Sector* sector : mSectors) {
		sector->mSprite->Draw(buffer, bufferWidth, bufferHight);
	}
}
