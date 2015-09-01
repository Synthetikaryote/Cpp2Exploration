#pragma once

#include <vector>
#include <Windows.h>
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

	vector<Sector*> mSectors;
};


