#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {

	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tempTexture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, texture, &src, &dest, NULL, NULL, flip);
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect dest, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, texture,NULL, &dest, NULL, NULL, flip);
}



