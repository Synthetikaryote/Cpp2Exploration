#ifndef INCLUDED_PLAYER_H
#define INCLUDED_PLAYER_H

#include <SGE.h>

using namespace SGE;

class Player
{
public:
	Player();
	~Player();

	void Load(const char* textureName);
	void Unload();
	void Update(float deltaTime);
	void Render(const SVector2 renderOffset);

	void SetPosition(SVector2 pos)	{ mPosition = pos; }
	SVector2 GetPosition() const	{ return mPosition; }

private:
	SGE_Sprite mSprite;
	SVector2 mPosition;
};

#endif // #ifndef INCLUDED_PLAYER_H