#include "TileMap.h"

TileMap::TileMap()
	: mSprites(nullptr)
	, mTiles(nullptr)
	, mNumSprites(0)
	, mWidth(64)
	, mHeight(64)
	, mTileSize(32)
{
}

TileMap::~TileMap()
{
	ASSERT(mSprites == nullptr, "Sprites not unloaded. Potential memory leak.");
	ASSERT(mTiles == nullptr, "Tiles not unloaded. Potential memory leak.");
}

void TileMap::Load(const char* texturePack)
{
	ASSERT(mSprites == nullptr, "Tile map already loaded.");
	ASSERT(mTiles == nullptr, "Tile map already loaded.");

	bool success = LoadTexturePack(texturePack);
	ASSERT(success, "Failed to load texture pack.");
}

void TileMap::Unload()
{
	if (mTiles != nullptr)
	{
		delete[] mTiles;
		mTiles = nullptr;
	}
	if (mSprites != nullptr)
	{
		for(int i = 0; i < mNumSprites; ++i)
		{
			mSprites[i].Unload();
		}
		delete[] mSprites;
		mSprites = nullptr;
	}
}

void TileMap::Update(float deltaTime)
{
}

void TileMap::Render(const SVector2 renderOffset, unsigned int seed)
{
	srand(50);

	for (int y = 0; y < mHeight; ++y)
	{
		for (int x = 0; x < mWidth; ++x)
		{
			int pickTile = rand() % 100;
			int tile;
			if(pickTile > 3)
			{
				tile = 0;
			}
			else
			{
				pickTile = rand() % 7 + 1;
				tile = pickTile;
			}

			SVector2 renderPos(static_cast<float>(x * mTileSize), static_cast<float>(y * mTileSize));
			renderPos += renderOffset;
			mSprites[tile].SetPosition(renderPos);
			mSprites[tile].Render();
		}
	}
}

bool TileMap::LoadLayout(const char* layout)
{
	FILE* file = nullptr;
	errno_t error = fopen_s(&file, layout, "r");
	if (error != 0)
	{
		return false;
	}

	fscanf_s(file, "%*s %d\n", &mWidth);
	fscanf_s(file, "%*s %d\n", &mHeight);
	fscanf_s(file, "%*s %d\n", &mTileSize);

	mTiles = new int[mWidth * mHeight];

	for (int y = 0; y < mHeight; ++y)
	{
		for (int x = 0; x < mWidth; ++x)
		{
			const int index = x + (y * mWidth);
			mTiles[index] = fgetc(file) - '0';
		}
		fgetc(file);
	}

	fclose(file);
	return true;
}

bool TileMap::LoadTexturePack(const char* texturePack)
{
	FILE* file = nullptr;
	errno_t error = fopen_s(&file, texturePack, "r");
	if (error != 0)
	{
		return false;
	}

	fscanf_s(file, "%*s %d\n", &mNumSprites);

	mSprites = new SGE_Sprite[mNumSprites];

	char filename[256];
	for(int i = 0; i < mNumSprites; ++i)
	{
		fscanf_s(file, "%s\n", filename, 256);
		mSprites[i].Load(filename);
	}

	fclose(file);
	return true;
}
