#include "Player.h"
#include "Uber.h"

Player::Player() {
	sprite.SetSize(6, 8);

	// some kinda robot
	sprite.SetData(
		" -  - "
		" (^^) "
		"  --  "
		"/|##|\\"
		"||##||"
		"^|__|^"
		" |  | "
		"()  ()");
	sprite.SetColors(
		"\x0F\x8F\x8F\x8F\x8F\x0F"
		"\x0F\x8F\x8B\x8B\x8F\x0F"
		"\x0F\x0F\x8F\x8F\x0F\x0F"
		"\x8F\x8F\x8F\x8F\x8F\x8F"
		"\x0F\x8F\x8F\x8F\x8F\x0F"
		"\x0F\x8F\x8F\x8F\x8F\x0F"
		"\x0F\x8F\x0F\x0F\x8F\x0F"
		"\x8F\x8F\x0F\x0F\x8F\x8F");
	ox = -3;
	oy = -6;
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
		x += (dx / d * moveSpeed * elapsed);
		y += (dy / d * moveSpeed * elapsed);
	}
}
