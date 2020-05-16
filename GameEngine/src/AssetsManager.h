#ifndef SRC_ASSETSMANAGER_H_
#define SRC_ASSETSMANAGER_H_

#include "main/Game.h"
#include <map>

/**********************************Singleton Class*************************************/

class AssetsManager {
private:
	AssetsManager(){}
	~AssetsManager(){}

	std::map<std::string, SDL_Texture*> textures;
	SDL_Texture* tex;

public:
	static AssetsManager& getInstance() {
		static AssetsManager am;
		return am;
	}

	AssetsManager(AssetsManager const&) = delete;

	void operator =(AssetsManager const&) = delete;

	SDL_Texture* getTexture(std::string textureName) {
		return textures[textureName];
	}

	void LoadTexture();
};

#endif
