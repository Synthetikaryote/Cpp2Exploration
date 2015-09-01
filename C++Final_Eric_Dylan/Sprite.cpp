#include "Sprite.h"

Sprite::Sprite() {
}
Sprite::Sprite(int width, int height) {
	SetSize(width, height);
}

Sprite::~Sprite()
{
	delete[] data;
}

void Sprite::SetSize(int width, int height) {
	w = width;
	h = height;
	data = new CHAR_INFO[height * width];
}

void Sprite::Update(float elapsed) {

}

void Sprite::Draw(CHAR_INFO* buffer, int bufferWidth, int bufferHeight) {
	for (int r = 0; r < h; ++r) {
		for (int c = 0; c < w; ++c) {
			if (c + x >= 0 && c + x < bufferWidth && r + y >= 0 && r + y < bufferHeight) {
				buffer[(r + y) * bufferWidth + c + x] = data[r * w + c];
			}
		}
	}
}

void Sprite::SetData(string characters) {
	for (int r = 0; r < h; ++r)
		for (int c = 0; c < w; ++c)
			data[r * w + c].Char.AsciiChar = characters[r * w + c];
}

void Sprite::SetColors(string colors) {
	for (int r = 0; r < h; ++r)
		for (int c = 0; c < w; ++c)
			data[r * w + c].Attributes = colors[r * w + c];
}