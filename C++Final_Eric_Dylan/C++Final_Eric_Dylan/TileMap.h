#ifndef INCLUDED_TILEMAP_H
#define INCLUDED_TILEMAP_H

#include <SGE.h>

using namespace SGE;
using namespace std;

class TileMap
{
public:
	TileMap();
	~TileMap();

	void Load(const char* layout, const char* texturePack);
	void Unload();
	void Update(float deltaTime);
	void Render(const SVector2 renderOffset);

	//TODO for tile based game
	void Sane(const char* fileName);
	int GetTile(SVector2 pos);
	void SetTile(SVector2 pos, int value);

	int GetWidth() const {return mWidth * mTileSize;}
	int GetHight() const {return mWidth * mTileSize;}
private:
	NONCOPYABLE(TileMap);
	
	bool LoadLayout(const char* layout);
	bool LoadTexturePack(const char* texturePack);

	SGE_Sprite* mSprites;
	int* mTiles;

	int mNumSprites;
	int mWidth;
	int mHeight;
	int mTileSize;
};

#endif // #ifndef INCLUDED_TILEMAP_H