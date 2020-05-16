#ifndef SRC_TILEMAP_TILEMAP_H_
#define SRC_TILEMAP_TILEMAP_H_

#include "../main/Game.h"
#include "../Vector2D.h"
#include "Tile.h"

class TileMap {
private:
	int numTilesAcross, numTilesDown;
	int visibleTilesX, visibleTilesY;
	int mapWidth, mapHeight;

	int map[64][100];	//height*width
	Tile tiles[6][10];

	SDL_Texture* tex;
	SDL_Rect TileRect, destRect;

	Vector2D cameraPos;
	Vector2D tileOffset;

public:
	static Vector2D offset;

	TileMap();
	~TileMap();

	void init();
	void loadMap(const char* path);
	void loadTileset(int numTilesAcross, int numTilesDown);
	void updateMap();
	void drawMap();
	void setBounds();
	void setPosition(const Vector2D& playerPos);	//we take, playerPos = cameraPos
	void setPosition(float x, float y);
	int getTileIndex(int x, int y) {return (map[x][y]);}

};

#endif
