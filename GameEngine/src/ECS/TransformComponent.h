#ifndef SRC_ECS_TRANSFORMCOMPONENT_H_
#define SRC_ECS_TRANSFORMCOMPONENT_H_

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {
public:

	Vector2D position;
	Vector2D velocity;

	float speed = 0.1f;
	int width = 48;
	int height = 61;
	float scale = 1.0f;

	TransformComponent() {
		position.origin();
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, float scale) {
		position.x = x;
		position.y = y;
		this->scale = scale;
	}

	TransformComponent(float x, float y, int w, int h, float scale) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		this->scale = scale;
	}

	void init() override {
		velocity.origin();
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};

#endif
