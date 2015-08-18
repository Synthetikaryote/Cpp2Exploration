#include "PlayState.h"
#include "FrontEndState.h"

GameContext gameContext;
GameState* currentState = nullptr;
StateTransition transition = StateTransition::GoToFrontEnd;
bool quit = false;

void SGE_Initialize()
{
}

void SGE_Terminate()
{
}

bool SGE_Update(float deltaTime)
{
	if(transition != StateTransition::None)
	{
		if(currentState != nullptr)
		{
			currentState->Unload();
			delete currentState;
			currentState = nullptr;
		}
		switch(transition)
		{
		case StateTransition::GoToFrontEnd:
		currentState = new FrontendState(gameContext);
		currentState->Load();
			break;
		case StateTransition::GoToGamePlay:
		currentState = new PlayState(gameContext);
		currentState->Load();
			break;
		case StateTransition::Quit:
			quit = true;
			break;
		}
	}

	if(currentState != nullptr)
	{
		transition = currentState->Update(deltaTime);
	}

	return quit;
}

void SGE_Render()
{
	if(currentState != nullptr)
	{
		currentState->Render();
	}
}