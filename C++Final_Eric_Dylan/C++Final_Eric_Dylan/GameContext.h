#ifndef INCLUDED_GAMECONTEXT_H
#define INCLUDED_GAMECONTEXT_H

class GameContext
{
public:
	GameContext();
	~GameContext();

	void SetCurrentLevel(int level) {mCurrentLevel = level;}
	int GetCurrentLevel() { return mCurrentLevel; }

private:
	int mCurrentLevel;
};

#endif // #ifndef INCLUDED_GAMECONTEXT_H