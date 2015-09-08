#pragma once

#include <vector>
#include <Windows.h>
#include <memory>
#include "Sector.h"


class Map
{
public:
	Map();
	~Map();

	int viewX, viewY;
	void Update(float elapsed);
	void Draw(CHAR_INFO* buffer, int bufferHight, int bufferWidth);
	void Spiral( int X, int Y, int sizeX, int sizeY);
	CHAR_INFO at(int x, int y);
	void worldXYToSectorXY(int x, int y, int& sectorX, int& sectorY);

	vector<shared_ptr<Sector>> mSectors;

	vector<int> applesCollected;
};


