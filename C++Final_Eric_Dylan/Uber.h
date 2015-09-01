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

	bool IsKeyDown(int vk) {
		return GetAsyncKeyState(vk) & 0x8000;
	}
private:
	Uber() {};                   // Constructor? (the {} brackets) are needed here.

	Uber(Uber const&) = delete;
	void operator=(Uber const&) = delete;

};