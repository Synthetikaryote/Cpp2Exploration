#include "Player.h"
#include "Uber.h"
#include <iostream>
#include <cmath>

Player::Player() {
	sprite.SetSize(3, 4);

	// some kinda robot
	sprite.SetData(
		" \1 "
		"/V\\"
		" ^ "
		"/ \\");
	sprite.SetColors(
		"\x2F\x2F\x2F"
		"\x2F\x2F\x2F"
		"\x2F\x2F\x2F"
		"\x2F\x2F\x2F");
	ox = -1;
	oy = -sprite.h;
}

Player::~Player() {
}

bool Player::CheckLocations(vector<point> locations) {
	Uber& uber = Uber::getInstance();
	bool foundApple = false;
	int appleX, appleY;
	bool pathClear = true;
	for (point loc : locations) {
		CHAR_INFO* ci;
		ci = uber.map.at(loc.x, loc.y);
		if (ci != nullptr) {
			unsigned char at = (*ci).Char.AsciiChar;
			if (at == 235) {
				foundApple = true;
				appleX = loc.x;
				appleY = loc.y;
			}
			if (!(at == ' ' || at == 235))
				pathClear = false;
		}
	}
	if (pathClear && foundApple)
		GrabApple(appleX, appleY);
	return pathClear;
}

bool Player::CheckX(int x) {
	vector<point> locations;
	for (int r = 0; r < sprite.h; ++r)
		locations.push_back(point((int)x + ox + (x > this->x ? sprite.w - 1 : 0), (int)y + oy + r));
	return CheckLocations(locations);
}

bool Player::CheckY(int y) {
	vector<point> locations;
	for (int c = 0; c < sprite.w; ++c)
		locations.push_back(point((int)x + ox + c, (int)y + oy + (y > this->y ? sprite.h - 1 : 0)));
	return CheckLocations(locations);
}

void Player::Update(float elapsed) {
	Character::Update(elapsed);

	Uber& uber = Uber::getInstance();
	int dx = 0;
	int dy = 0;
	if (uber.IsKeyDown(VK_RIGHT)) dx++;
	if (uber.IsKeyDown(VK_LEFT)) dx--;
	if (uber.IsKeyDown(VK_UP)) dy--;
	if (uber.IsKeyDown(VK_DOWN)) dy++;

	float d = sqrt(dx * dx + dy * dy);
	if (d > 0) {
		if (CheckX(x + dx / d * moveSpeed * elapsed))
			x += dx / d * moveSpeed * elapsed;
		if (CheckY(y + dy / d * moveSpeed * elapsed))
			y += dy / d * moveSpeed * elapsed;

		// align diagonal movement to perfect diagonals only
		//if (dx && dy) {
		//	float intPartX, intPartY;
		//	float fracPartX = modf(x, &intPartX);
		//	float fracPartY = modf(y, &intPartY);
		//	float lowestFractionalPart = min(fracPartX, fracPartY);
		//	x = intPartX + lowestFractionalPart;
		//	y = intPartY + lowestFractionalPart;
		//}
	}
}

void Player::GrabApple(int x, int y) {
	Uber& uber = Uber::getInstance();
	CHAR_INFO* ci = uber.map.at(x, y);
	if (ci != nullptr) {
		(*ci).Char.AsciiChar = ' ';
	}
	shared_ptr<Sector> sector = uber.map.findSectorAt(x, y);
	uber.map.applesCollected.push_back(sector.get()->mSeed);
	uber.player.mFullness = min(20, uber.player.mFullness + 5);
	uber.player.timeLeftUntillHungry = 5;
}