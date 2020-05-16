#ifndef SRC_ECS_KEYBOARDCONTROLLER_H_
#define SRC_ECS_KEYBOARDCONTROLLER_H_

#include "../main/Game.h"
#include "components.h"

class KeyboardController:public Component {
public:
	SpriteComponent* sprite;
	TransformComponent* transform;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if(Game::event.type == SDL_KEYDOWN) {
			switch(Game::event.key.keysym.sym) {
				case SDLK_w:
					transform->velocity.y = -1.0f;
					sprite->play("Walk");
					break;

				case SDLK_a:
					transform->velocity.x = -1.0f;
					sprite->play("Walk");
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					break;

				case SDLK_d:
					transform->velocity.x = 1.0f;
					sprite->play("Walk");
					break;

				case SDLK_s:
					transform->velocity.y = 1.0f;
					sprite->play("Walk");
					break;

				case SDLK_SPACE:
					transform->velocity.y = -3.0f;
					sprite->play("Jump");
					break;

				default:
					break;
			}
		} else if (Game::event.type == SDL_KEYUP) {
			switch(Game::event.key.keysym.sym) {
				case SDLK_w:
					transform->velocity.y = 0.0f;
					sprite->play("Idle");
					break;

				case SDLK_a:
					transform->velocity.x = 0.0f;
					sprite->play("Idle");
					sprite->spriteFlip = SDL_FLIP_NONE;
					break;

				case SDLK_d:
					transform->velocity.x = 0.0f;
					sprite->play("Idle");
					break;

				case SDLK_s:
					transform->velocity.y = 0.0f;
					sprite->play("Idle");
					break;

				case SDLK_SPACE:
					transform->velocity.y = 1.0f;
					sprite->play("Idle");
					break;

				case SDLK_ESCAPE:
					Game::isRunning = false;
					break;
				default:
					break;
			}
		}
	}

};



#endif
