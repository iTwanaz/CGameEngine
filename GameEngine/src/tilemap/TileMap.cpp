#include "TileMap.h"
#include <fstream>
#include "../TextureManager.h"
#include "../AssetsManager.h"

Vector2D TileMap::offset;

TileMap::TileMap() {}

TileMap::~TileMap() {
//	for(int i = 0; i < numTilesDown; i++) {
//		for(int j = 0; j < numTilesAcross; j++) {
//			delete tiles[i][j];
//		}
//	}
}

void TileMap:: init() {

	tex = AssetsManager::getInstance().getTexture("sSwamp");
	destRect.w = Tile::tileWidth;
	destRect.h = Tile::tileHeight;

	//actual visible tiles on the screen to be drawn
	visibleTilesX = WINDOWWIDTH / Tile::tileWidth;
	visibleTilesY = WINDOWHEIGHT / Tile::tileHeight;

}


void TileMap::loadTileset(int numTilesAcross, int numTilesDown) {

	this->numTilesAcross = numTilesAcross;
	this->numTilesDown = numTilesDown;

	for(int i = 0; i < numTilesDown; i++) {
		for(int j = 0; j < numTilesAcross; j++) {

			//storing the srcRect value for each tile in the tile-set
			TileRect = {j * Tile::tileWidth, i * Tile::tileHeight, Tile::tileWidth, Tile::tileHeight};
//			tiles[i][j] = new Tile(TileRect, Tile::DEFAULT);
			if(j == numTilesAcross - 1) {
				tiles[i][j] = Tile(TileRect, Tile::BLOCKED);
			}else{
				tiles[i][j] = Tile(TileRect, Tile::NORMAL);
			}
		}
	}

}


void TileMap::loadMap(const char* path) {

	std::ifstream mapFile(path);

	if(mapFile.is_open()){

		mapFile >> mapWidth;
		mapFile >> mapHeight;

		for(int row = 0; row < mapHeight; row++) {
			for(int col = 0; col < mapWidth; col++) {
				mapFile >> map[row][col];
//				std::cout << map[row][col] << " ";
			}
//			std::cout << std:: endl;
		}
	} else {
		std::cerr << "File not Found!" << std::endl;
	}
}

void TileMap::setPosition(float x, float y) {
	cameraPos.x = x;
	cameraPos.y = y;
}

void TileMap::setPosition(const Vector2D& playerPos) {

	cameraPos.x = playerPos.x;
	cameraPos.y = playerPos.y;

//	std::cout << cameraPos << std::endl;
//	std::cout << "PlayerPos: " << playerPos << "*" << std::endl;
//	std::cout << "Offset: " << offset << std::endl;
//	std::cout << "TileOffset: " << tileOffset << std::endl;

}


void TileMap::updateMap() {

	// Calculate Top-Leftmost visible tile from the middle of the screen
	offset.x = cameraPos.x - visibleTilesX / 2;
	offset.y = cameraPos.y - visibleTilesY / 2;

	tileOffset.x = (offset.x - (int)offset.x) * Tile::tileWidth;
	tileOffset.y = (offset.y - (int)offset.y) * Tile::tileHeight;

	setBounds();
}


void TileMap::setBounds() {

//if the map approaches the boundary of the game, clamp the camera.
	if(offset.x < 0) offset.x = 0;
	if(offset.y < 0) offset.y = 0;
	if(offset.x > mapWidth - visibleTilesX) offset.x = mapWidth - visibleTilesX - 1;	//as we are drawing 1 extra tile in the draw fun
	if(offset.y > mapHeight - visibleTilesY) offset.y = mapHeight - visibleTilesY - 1;//needs to be clamped 1 tile ahead.
}


void TileMap::drawMap() {

	for(int row = 0; row < visibleTilesY + 1; row++) {
		for(int col = -1; col < visibleTilesX + 1; col++) {
//			std::cout << map[row + (int)offset.y][col + (int)offset.x] << " ";

			int tileIndex = getTileIndex(row + (int)offset.y, col + (int)offset.x);

			if(tileIndex == -1) continue;

			int r = tileIndex / numTilesAcross;
			int c = tileIndex % numTilesAcross;
//			std::cout << r << " " << c << "*";
//			std::cout << tiles[r][c].getTilePos().x << "," << tiles[r][c].getTilePos().y << " ";

//			std::cout << "TileOffset: " << tileOffset << "*" << std::endl;
			if(tileOffset.x < 0) {
				tileOffset.x = 0;
			}else if(tileOffset.y < 0) {
				tileOffset.y = 0;
			}

			if(offset.x >= mapWidth - visibleTilesX - 1) tileOffset.x = 0;
			if(offset.y >= mapHeight - visibleTilesY - 1) tileOffset.y = 0;


//			std::cout << "Offset: " << offset << std::endl;

			destRect.x = col * Tile::tileWidth - tileOffset.x;
			destRect.y = row * Tile::tileHeight - tileOffset.y;

			TextureManager::getInstance().Draw(tex, tiles[r][c].getTilePos(), destRect, SDL_FLIP_NONE);

		}
//		std::cout << std::endl;
	}

}



