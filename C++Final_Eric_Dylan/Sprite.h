#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class Sprite
{
public:
	CHAR_INFO* data;
	int x, y, w, h;
	Sprite(int width, int height);
	~Sprite();
	void SetData(string characters);

	void Update(float elapsed);
	void Draw(CHAR_INFO* buffer, int bufferWidth, int bufferHeight);
};

