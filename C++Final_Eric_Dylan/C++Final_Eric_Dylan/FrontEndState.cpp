#include "FrontEndState.h"

FrontendState::FrontendState(GameContext& context)
: GameState(context)
{
}

FrontendState::~FrontendState()
{
}


void FrontendState::Load()
{
	mFont.Load(64, true, false);
	mButtonLevel1.Load("button_on.png", "button_off.png");
	mButtonLevel1.SetText("Level 1", 255, 255, 255);
	mButtonLevel1.SetPosition(200.0f, 400.0f);

	mButtonQuit.Load("button_on.png", "button_off.png");
	mButtonQuit.SetText("Quit", 255, 255, 255);
	mButtonQuit.SetPosition(200.0f, 500.0f);

	mCursor.Load("sword.png");
}

void FrontendState::Unload()
{
	mFont.Unload();
	mButtonLevel1.Unload();
	mButtonQuit.Unload();
	mCursor.Unload();
}

StateTransition FrontendState::Update(float deltaTime)
{
	mButtonLevel1.Update(deltaTime);
	mButtonQuit.Update(deltaTime);
	mCursor.Update(deltaTime);

	StateTransition transision = StateTransition::None;

	if(mButtonLevel1.IsPressed())
	{
		mGameContext.SetCurrentLevel(1);
		transision = StateTransition::GoToGamePlay;
	}
	if(mButtonQuit.IsPressed())
	{
		transision = StateTransition::Quit;
	}
	return transision;
}

void FrontendState::Render()
{
	mFont.Print("Adventure Game", 200, 300);
	mButtonLevel1.Render();
	mButtonQuit.Render();
	mCursor.Render();
}