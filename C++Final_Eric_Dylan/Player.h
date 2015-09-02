#pragma once
#include "Character.h"
#include <Windows.h>


class Player : public Character
{
public:
	Player();
	~Player();
	float moveSpeed = 15.0f;
	int apples = 0;
	void Update(float elapsed) override;
	bool CheckX(int x);
	bool CheckY(int y);
};

