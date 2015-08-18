#ifndef INCLUDED_FRONTENDSTATE_H
#define INCLUDED_FRONTENDSTATE_H

#include "GameState.h"
#include <SGE.h>
using namespace SGE;

class FrontendState : public GameState
{
public:
	FrontendState(GameContext& context);
	virtual ~FrontendState();

	virtual void Load();
	virtual void Unload();
	virtual StateTransition Update(float deltaTime);
	virtual void Render();
private:
	SGE_Font mFont;
	SGE_Button mButtonLevel1;
	SGE_Button mButtonQuit;
	SGE_Cursor mCursor;
};

#endif // #ifndef INCLUDED_GAMESTATE_H