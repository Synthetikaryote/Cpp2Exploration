#pragma once
#include "Character.h"
#include <Windows.h>


class Player : public Character
{
public:
	Player();
	~Player();
	void Update(float elapsed) override;
};

