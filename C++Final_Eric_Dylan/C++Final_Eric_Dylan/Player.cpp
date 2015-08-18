#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Load(const char* textureName)
{
	mSprite.Load(textureName);
}

void Player::Unload()
{
	mSprite.Unload();
}

void Player::Update(float deltaTime)
{
	const float kSpeed = 300.0f;
	if (Input_IsKeyDown(Keys::RIGHT))
	{
		mPosition.x += kSpeed * deltaTime;
	}
	else if (Input_IsKeyDown(Keys::LEFT))
	{
		mPosition.x -= kSpeed * deltaTime;
	}

	if (Input_IsKeyDown(Keys::DOWN))
	{
		mPosition.y += kSpeed * deltaTime;
	}
	else if (Input_IsKeyDown(Keys::UP))
	{
		mPosition.y -= kSpeed * deltaTime;
	}
}

void Player::Render(const SVector2 renderOffset)
{
	//pass a camera not a vector2
	const int kWidth = mSprite.GetWidth();
	const int kHeight = mSprite.GetHeight();

	SVector2 renderPosition;
	renderPosition.x = mPosition.x - (kWidth * 0.5f) + renderOffset.x;
	renderPosition.y = mPosition.y - (kHeight * 0.5f) + renderOffset.y;

	//if (camera.IsVisible(renderPosition, renderPosition)
	mSprite.SetPosition(renderPosition);
	mSprite.Render();
}