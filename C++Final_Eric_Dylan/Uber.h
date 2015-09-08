#pragma once

#include "Map.h"
#include "Character.h"
#include "Player.h"
#include <vector>
using namespace std;

// singleton design pattern from here:
// http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
class Uber {
public:
	static Uber& getInstance() {
		static Uber instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	const int sectorWidth = 64;
	const int sectorHeight = 64;

	Map map;

	Player player;
	vector<Character*> characters;
	Sprite tree;

	int baseSeed = 1;

	bool IsKeyDown(int vk) {
		return ((GetAsyncKeyState(vk) & 0x8000) != 0);
	}

	void printAt(CHAR_INFO* buffer, int bufferWidth, int bufferHeight, string message, byte color, int x, int y) {
		for (int i = 0; i < static_cast<int>(message.length()); ++i) {
			if (x + i < bufferWidth && y < bufferHeight) {
				buffer[y * bufferWidth + x + i].Attributes = color;
				buffer[y * bufferWidth + x + i].Char.AsciiChar = message[i];
			}
		}
	}
private:
	Uber() {};                   // Constructor? (the {} brackets) are needed here.

	Uber(Uber const&) = delete;
	void operator=(Uber const&) = delete;
};