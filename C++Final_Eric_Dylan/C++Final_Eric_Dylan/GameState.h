#ifndef INCLUDED_GAMESTATE_H
#define INCLUDED_GAMESTATE_H


#include "GameContext.h"

enum class StateTransition
{
	None,
	GoToFrontEnd,
	GoToGamePlay,
	Quit
};

class GameState
{
public:
	GameState(GameContext& context);
	virtual ~GameState();

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual StateTransition Update(float deltaTime) = 0;
	virtual void Render() = 0;
protected:
	GameContext& mGameContext;
};

#endif // #ifndef INCLUDED_GAMESTATE_H