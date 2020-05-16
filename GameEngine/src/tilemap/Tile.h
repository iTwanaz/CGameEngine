#ifndef SRC_TILEMAP_TILE_H_
#define SRC_TILEMAP_TILE_H_

#include "../main/Game.h"

class Tile {
private:
	SDL_Rect TileRect;
	int TileType;

public:
	const static int DEFAULT = 0;
	const static int NORMAL = 1;
	const static int BLOCKED = 2;

	const static int tileWidth = 32;
	const static int tileHeight = 32;

	Tile();
	~Tile();

	Tile(const SDL_Rect rect, int type);


	SDL_Rect& getTilePos();
	int getTileType();

};


#endif
