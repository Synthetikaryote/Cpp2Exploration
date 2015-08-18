#ifndef INCLUDED_PLAYSTATE_H
#define INCLUDED_PLAYSTATE_H

#include "GameState.h"
#include "Player.h"
#include "MapPiece.h"

class PlayState : public GameState
{
public:
	PlayState(GameContext& context);
	virtual ~PlayState();

	virtual void Load();
	virtual void Unload();
	virtual StateTransition Update(float deltaTime);
	virtual void Render();

private:
	Player mPlayer;
	MapPiece mMap;
};

#endif // #ifndef INCLUDED_PLAYSTATE_H