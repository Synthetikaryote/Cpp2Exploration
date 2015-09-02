#include "Player.h"
#include "Uber.h"
#include <iostream>

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
		unsigned char at = uber.map.at(loc.x, loc.y).Char.AsciiChar;
		if (at == 235) {
			foundApple = true;
			appleX = loc.x;
			appleY = loc.y;
		}
		if (!(at == ' ' || at == 235))
			pathClear = false;
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
	if (uber.IsKeyDown(VK_RIGHT)) if (CheckX(x + 1)) dx++;
	if (uber.IsKeyDown(VK_LEFT)) if (CheckX(x - 1)) dx--;
	if (uber.IsKeyDown(VK_UP)) if (CheckY(y - 1)) dy--;
	if (uber.IsKeyDown(VK_DOWN)) if (CheckY(y + 1)) dy++;
	float d = sqrt(dx * dx + dy * dy);
	if (d > 0) {
		x += dx / d * moveSpeed * elapsed;
		y += dy / d * moveSpeed * elapsed;
	}

}

void Player::GrabApple(int x, int y) {

}