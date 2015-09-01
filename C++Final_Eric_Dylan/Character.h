#pragma once
#include <Windows.h>
#include "Sprite.h"

class Character
{
public:
	Character();
	~Character();
	Sprite sprite;
	float x, y, ox, oy;
	virtual void Update(float elapsed);
	virtual void Draw(CHAR_INFO* buffer, int bufferWidth, int bufferHeight);
};

