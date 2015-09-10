#include <iostream>
#include <Windows.h>
#include <chrono>
#include "Uber.h"
#include "Sector.h"
#include <sstream>
#include <time.h>

using namespace std;
using namespace std::chrono;

float targetFramesPerSecond = 80.0f;
float spf = 1.0f / targetFramesPerSecond;
const int screenWidth = 64;
const int screenHeight = 64;
CHAR_INFO buffer[screenHeight * screenWidth];

int calculatedFPS = 0;

Uber &uber = Uber::getInstance();
void initGame();
void update(float elapsed);
void draw();
bool inGame = true;

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

	COORD dwBufferSize = { screenWidth, screenHeight };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, screenWidth - 1, screenHeight - 1 };
	SetConsoleWindowInfo(hOutput, TRUE, &rcRegion);
	SetConsoleScreenBufferSize(hOutput, dwBufferSize);

	initGame();

	uber.baseSeed = time(NULL);

	while (1) {
		float t = time();

		// redraw 60 fps
		if (t - lastFrame >= spf) {
			float elapsed = t - lastFrame;
			lastFrame = t;

			if (uber.IsKeyDown(VK_ESCAPE)) {
				break;
			}

			update(elapsed);

			draw();

			WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
		}
	}
}

void initGame() {
	// add the player to the list of characters
	uber.characters.push_back(&(uber.player));

	uber.player.x = screenWidth / 2;
	uber.player.y = screenHeight / 2;
	uber.player.sprite.x = uber.player.x + uber.player.ox;
	uber.player.sprite.y = uber.player.y + uber.player.oy;

	uber.tree.SetSize(3,4);
	uber.tree.SetData(
		" ^ "
		"/|\\"
		"/|\\"
		"^|^");
	uber.tree.SetColors(
		"\x2A\x2A\x2A"
		"\x2A\x2E\x2A"
		"\x2A\x2E\x2A"
		"\x2A\x2E\x2A");
}

void update(float elapsed) {
	if (inGame) {
		// update the characters
		for (Character* character : uber.characters) {
			character->Update(elapsed);
		}

		if (uber.player.mFullness <= 0)
		{
			//reset game
			uber.player.mFullness = 20;
			uber.player.timeLeftUntilHungry = uber.player.secondsPerHunger;
			uber.map.mSectors.clear();
			uber.map.applesCollected.clear();
			uber.player.x = 32;
			uber.player.y = 32;
			uber.baseSeed = time(NULL);
			inGame = false;

			for (int i = 0; i < screenHeight * screenWidth; ++i) {
				CHAR_INFO ci;
				ci.Char.AsciiChar = ' ';
				ci.Attributes = 0x00;
				buffer[i] = ci;
			}
		}

		// update the map
		uber.map.viewX = -(static_cast<int>(uber.player.x) - screenWidth / 2);
		uber.map.viewY = -(static_cast<int>(uber.player.y) - screenHeight / 2);
		uber.map.Update(elapsed);
	}
	else {
		if (uber.IsKeyDown(VK_RETURN)) {
			inGame = true;
		}
	}

	calculatedFPS = (int)(1.0f / elapsed);
}

void draw() {
	if (inGame) {
		uber.map.Draw(buffer, screenWidth, screenHeight);
		// draw everything
		for (Character* character : uber.characters) {
			character->Draw(buffer, screenWidth, screenHeight);
		}

		// show FPS
		stringstream message;
		//message << "FPS: " << calculatedFPS << "  Player at (" << uber.player.x << ", " << uber.player.y << ")";
		message << "Apples collected: " << uber.map.applesCollected.size();
		uber.printAt(buffer, screenWidth, screenHeight, message.str(), 0x0F, 1, 1);

		message.str("Fullness: [");
		for (int i = 0; i < uber.player.mFullness; ++i)
			message << "|";
		for (int i = 0; i < max(0, uber.player.maxFullness - uber.player.mFullness); ++i)
			message << " ";
		message << "]";
		uber.printAt(buffer, screenWidth, screenHeight, message.str(), 0x0F, 25, 1);

		message.str("Use arrow keys to move.  Find and collect apples to stay alive!");
		uber.printAt(buffer, screenWidth, screenHeight, message.str(), sin(time() * 5) > 0 ? 0x0F : 0x08, 0, 62);
	}
	else {
		stringstream message;
		message << "GAME OVER";
		uber.printAt(buffer, screenWidth, screenHeight, message.str(), 0x0F, 27, 30);
		message.str("Press enter to restart");
		uber.printAt(buffer, screenWidth, screenHeight, message.str(), 0x0F, 21, 34);
	}
}