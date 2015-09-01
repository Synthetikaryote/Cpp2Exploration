#include "Sprite.h"


Sprite::Sprite(int width, int height) {
	this->width = width;
	this->height = height;
	buffer = new CHAR_INFO*[height];
	for (int r = 0; r < height; ++r)
		buffer[r] = new CHAR_INFO[width];
}


Sprite::~Sprite()
{
	for (int r = 0; r < height; ++r)
		delete[] buffer[r];
	delete[] buffer;
}
