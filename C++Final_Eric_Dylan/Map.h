#pragma once

#include <vector>

class Map
{
public:
	Map();
	~Map();

	void Update(float elapsed);
	void Draw(CHAR_INFO* buffer);
};

