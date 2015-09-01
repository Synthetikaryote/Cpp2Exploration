#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class Sprite
{
public:
	CHAR_INFO** buffer;
	int width;
	int height;
	Sprite(int width, int height);
	~Sprite();
	void SetData(string characters);

	void Update(float elapsed);
	void Draw(CHAR_INFO* buffer);
};

