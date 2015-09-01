#include "Player.h"
#include "Uber.h"

Player::Player() {
	sprite.SetSize(3, 4);

	// some kinda robot
	sprite.SetData(
		" \1 "
		"/#\\"
		" ^ "
		"/ \\");
	sprite.SetColors(
		"\x2F\x2F\x2F"
		"\x2F\x2F\x2F"
		"\x2F\x2F\x2F"
		"\x2F\x2F\x2F");
	ox = -2;
	oy = -3;
}

Player::~Player() {
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
		x += dx / d * moveSpeed * elapsed;
		y += dy / d * moveSpeed * elapsed;
	}
}
