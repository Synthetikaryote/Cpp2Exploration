#pragma once

#include <vector>
#include <Windows.h>

class Map
{
public:
	Map();
	~Map();

	void Update(float elapsed);
	void Draw(CHAR_INFO* buffer, int x, int y);
};

