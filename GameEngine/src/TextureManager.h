#ifndef SRC_TEXTUREMANAGER_H_
#define SRC_TEXTUREMANAGER_H_

#include "main/Game.h"

class TextureManager {
private:
	TextureManager() {}
	~TextureManager() {}

public:

	static TextureManager& getInstance() {
		static TextureManager tm;
		return tm;
	}

	TextureManager(TextureManager const&) = delete;
	void operator =(TextureManager const&) = delete;

	SDL_Texture* LoadTexture(const char* fileName);
	void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
	void Draw(SDL_Texture* texture, SDL_Rect dest, SDL_RendererFlip flip);

};

#endif
