#pragma once
#include "Character.h"
#include <Windows.h>


class Player : public Character
{
public:
	Player();
	~Player();
	float moveSpeed = 25.0f;
	void Update(float elapsed) override;
};

