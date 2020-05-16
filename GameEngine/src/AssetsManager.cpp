#include "AssetsManager.h"
#include "TextureManager.h"

void AssetsManager::LoadTexture() {

	auto load = [&](std::string tName, const char* path) {
		tex = TextureManager::getInstance().LoadTexture(path);
		textures[tName] = tex;
	};


	//player
	load("sPlayer", "assets/movables/player/player_anims.PNG");

	//background
	load("sBg1", "assets/maps/Background/plx-1.PNG");
	load("sBg2", "assets/maps/Background/plx-2.PNG");
	load("sBg3", "assets/maps/Background/plx-3.PNG");
	load("sBg4", "assets/maps/Background/plx-4.PNG");
	load("sBg5", "assets/maps/Background/plx-5.PNG");

	//tile-set
	load("sSwamp", "assets/maps/Tiles/Tileset.png");

}

