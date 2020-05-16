#include "Tile.h"

Tile::Tile() {}

Tile::~Tile() {}

Tile::Tile(const SDL_Rect rect, int type) {
	TileRect = rect;
	TileType = type;
}

SDL_Rect& Tile::getTilePos() {return TileRect;}
int Tile::getTileType() {return TileType;}
