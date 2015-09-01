#include "Map.h"

Map::Map()
{
	Sector* newSector = new Sector(1234);
	mSectors.push_back(newSector);
}


Map::~Map()
{
	for (Sector* sector : mSectors) {
		delete sector;
	}
	mSectors.clear();
}

void Map::Update(float elapsed, int x, int y) {

}

void Map::Draw(CHAR_INFO* buffer, int bufferWidth, int bufferHight, int x, int y) {	
	for (Sector* sector : mSectors) {
		sector->mSprite->Draw(buffer, bufferWidth, bufferHight);
	}
}
