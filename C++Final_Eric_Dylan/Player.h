#pragma once
#include "Character.h"
#include <Windows.h>
#include <vector>
using namespace std;

struct point {
	int x, y;
	point() {}
	point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

class Player : public Character
{
public:
	Player();
	~Player();
	float moveSpeed = 20.0f;
	int apples = 0;
	void Update(float elapsed) override;
	bool CheckX(int x);
	bool CheckY(int y);
	bool CheckLocations(vector<point> locations);
	void GrabApple(int x, int y);

	float maxFullness = 20.f;
	float mFullness = maxFullness;
	float timeLeftUntilHungry = secondsPerHunger;
	float secondsPerHunger = 0.5f;
	float fullnessPerApple = 5.0f;
};

