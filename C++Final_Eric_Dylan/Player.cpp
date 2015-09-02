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

bool Player::CheckX(int x) {
	Uber& uber = Uber::getInstance();
	int mapX = (int)x + ox + (x > this->x ? sprite.w - 1: 0);
	for (int r = 0; r < sprite.h; ++r) {
		int mapY = (int)y + oy + r;

		unsigned char at = uber.map.at(mapX, mapY).Char.AsciiChar;
		if (!(at == ' ' || at == 235)) {
			return false;
		}
	}
	return true;
}

bool Player::CheckY(int y) {
	Uber& uber = Uber::getInstance();
	int mapY = (int)y + oy + (y > this->y ? sprite.h - 1 : 0);
	for (int c = 0; c < sprite.w; ++c) {
		int mapX = (int)x + ox + c;

		char at = uber.map.at(mapX, mapY).Char.AsciiChar;
		if (!(at == ' ' || at == 235)) {
			return false;
		}
	}
	return true;
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