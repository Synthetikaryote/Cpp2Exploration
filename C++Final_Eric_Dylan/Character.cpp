#include "Character.h"


Character::Character() {
}


Character::~Character() {
}

void Character::Update(float elapsed) {
	sprite.Update(elapsed);
}
void Character::Draw(CHAR_INFO* buffer, int bufferWidth, int bufferHeight) {
	sprite.Draw(buffer, bufferWidth, bufferHeight);
}