#include "PlayState.h"

PlayState::PlayState(GameContext& context)
: GameState(context)
{
}

PlayState::~PlayState()
{
}

void PlayState::Load()
{
	mPlayer.Load("mario.png");

	int levelSelected = mGameContext.GetCurrentLevel();

	if(levelSelected == 1)
	{
		mMap.Load("texturepack01.txt");
	}
}

void PlayState::Unload()
{
	mPlayer.Unload();
	mMap.Unload();
}

StateTransition PlayState::Update(float deltaTime)
{
	mPlayer.Update(deltaTime);
	mMap.Update(deltaTime);

	StateTransition transision = StateTransition::None;

	if(Input_IsKeyPressed(Keys::ESCAPE))
	{
		transision = StateTransition::GoToFrontEnd;
	}
	return transision;


	return StateTransition::None;
}

void PlayState::Render()
{
	SVector2 cameraTarget = mPlayer.GetPosition();

	const int kWinWidth = IniFile_GetInt("WinWidth", 800);
	const int kWinHight = IniFile_GetInt("WinHight", 800);

	SVector2 cameraBoundery;
	cameraBoundery.x = static_cast<float>(mMap.GetWidth() - kWinWidth);
	cameraBoundery.y = static_cast<float>(mMap.GetHight() - kWinHight);

	SVector2 cameraPostition;
	cameraPostition.x = cameraTarget.x - (kWinWidth * 0.5f);
	cameraPostition.y = cameraTarget.y - (kWinHight * 0.5f);
	cameraPostition.x = Clamp(cameraPostition.x, 0, cameraBoundery.x);
	cameraPostition.y = Clamp(cameraPostition.y, 0, cameraBoundery.y);

	SVector2 renderOffset = -cameraPostition;

	mMap.Render(renderOffset, 10);
	mPlayer.Render(renderOffset);
}



class Camera
{
public:
	void SetTarget(SVector2 pos);
	void SetBoundery(SVector2 min, SVector2 max);


	//check if the given vector is within the screen if so return true and change screenPosition to be the location to render the object
	bool IsVisible(SVector2 worlsPosition, SVector2& screenPosition, ...);
	
};