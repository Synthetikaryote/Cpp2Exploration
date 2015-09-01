#pragma once

#include <vector>
#include <Windows.h>
#include "Sector.h"

class Map
{
public:
	Map();
	~Map();

	void Update(float elapsed, int x, int y);
	void Draw(CHAR_INFO* buffer, int bufferHight, int bufferWidth, int x, int y);

	vector<Sector*> mSectors;
};


