#pragma once

#include "Map.h"
#include "Sprite.h"
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

	Map map;
	
	vector<Sprite> sprites;
	const int sectorWidth = 64;
	const int sectorHeight = 64;

private:
	Uber() {};                   // Constructor? (the {} brackets) are needed here.

	Uber(Uber const&) = delete;
	void operator=(Uber const&) = delete;

};