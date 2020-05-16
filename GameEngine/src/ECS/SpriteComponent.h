#ifndef SRC_ECS_SPRITECOMPONENT_H_
#define SRC_ECS_SPRITECOMPONENT_H_

#include "Components.h"
#include "SDL.h"
#include "Animation.h"
#include "../tileMap/TileMap.h"
#include <map>

class SpriteComponent : public Component {

private:
	TransformComponent* transform;
	SDL_Texture* texture;

	bool animated = false;
	int frames = 0;
	int speed = 150;

	int animIndex = 0;
	std::map<const char*, Animation> animations;

public:
	SDL_Rect srcRect, destRect;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(std::string path) {
		setTexture(path);
	}

	SpriteComponent(const char* path, bool isAnimated) {		//may take frames and speed as parameter for different objects//
		animated = isAnimated;

		Animation idleAnimation = Animation(0, 10, 100);
		Animation walkAnimation = Animation(1, 10, 100);
		Animation jumpAnimation = Animation(2, 10, 100);

		animations.emplace("Idle", idleAnimation);
		animations.emplace("Walk", walkAnimation);
		animations.emplace("Jump", jumpAnimation);

		play("Idle");

		setTexture(path);
	}

	void setTexture(std::string path) {
		texture = AssetsManager::getInstance().getTexture(path);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void update() override {

		if(animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = (transform->position.x - TileMap::offset.x) * Tile::tileWidth;
		destRect.y = (transform->position.y - TileMap::offset.y) * Tile::tileHeight;

	}

	void draw() override {
		TextureManager::getInstance().Draw(texture, srcRect, destRect, spriteFlip);
	}

	void play(const char* animName) {
		frames = animations[animName].frames;
		speed = animations[animName].speed;
		animIndex = animations[animName].index;
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}


};


#endif
