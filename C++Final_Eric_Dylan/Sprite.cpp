#include "Sprite.h"

Sprite::Sprite(int width, int height) {
	w = width;
	h = height;
	data = new CHAR_INFO*[height];
	for (int r = 0; r < height; ++r)
		data[r] = new CHAR_INFO[width];
}

Sprite::~Sprite()
{
	for (int r = 0; r < h; ++r)
		delete[] data[r];
	delete[] data;
}

void Sprite::Update(float elapsed) {

}

void Sprite::Draw(CHAR_INFO** buffer, int bufferWidth, int bufferHeight) {
	for (int r = 0; r < h; ++r) {
		for (int c = 0; c < w; ++c) {
			if (c + x >= 0 && c + x < bufferWidth && r + y >= 0 && r + y < bufferHeight) {
				buffer[r + x][c + y] = data[r][c];
			}
		}
	}
}