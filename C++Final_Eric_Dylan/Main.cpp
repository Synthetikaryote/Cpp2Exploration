#include <iostream>
#include <Windows.h>
#include <chrono>
#include "Uber.h"

using namespace std;
using namespace std::chrono;

float targetFramesPerSecond = 80.0f;
float spf = 1.0f / targetFramesPerSecond;
const int screenWidth = 64;
const int screenHeight = 64;

Uber uber;
void initGame();

high_resolution_clock::time_point timeStart = high_resolution_clock::now();
float time() {
	auto sinceStart = high_resolution_clock::now() - timeStart;
	return ((float)sinceStart.count()) * high_resolution_clock::period::num / high_resolution_clock::period::den;
}

void moveCursor(int x, int y) {
	COORD Position;
	Position.X = x;
	Position.Y = y;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, Position);
}

int main() {
	byte keys[256];
	int i = 0;

	float lastTime = 0.0f;
	float lastFrame = 0.0f;

	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (GetCurrentConsoleFontEx(hOutput, false, &info)) {
		COORD dwFontSize = { 8, 8 };
		info.dwFontSize = dwFontSize;
		SetCurrentConsoleFontEx(hOutput, false, &info);
	}

	CHAR_INFO buffer[screenHeight][screenWidth];
	COORD dwBufferSize = { screenWidth, screenHeight };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, screenWidth - 1, screenHeight - 1 };
	SetConsoleWindowInfo(hOutput, TRUE, &rcRegion);
	SetConsoleScreenBufferSize(hOutput, dwBufferSize);

	initGame();

	while (1) {
		float t = time();

		GetKeyboardState(keys);
		if (keys[VK_ESCAPE] & 1) {
			break;
		}

		// redraw 60 fps
		if (t - lastFrame >= spf) {
			float elapsed = t - lastFrame;
			lastFrame = t;

			for (int r = 0; r < screenHeight; ++r) {
				for (int c = 0; c < screenWidth; ++c) {
					buffer[r][c].Char.AsciiChar = (char)(rand() % 255);
					buffer[r][c].Attributes = 0x28; //(char)(rand() % 256);
				}
			}

			WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

			// show FPS
			moveCursor(0, 0);
			cout << "FPS: " << (int)(1.0f / elapsed);
		}
	}

	system("pause");
}

void initGame() {

}