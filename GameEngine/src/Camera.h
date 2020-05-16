#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

#include "Vector2D.h"

class Camera {
public:
	Vector2D position;
	Vector2D offset;

private:
	Camera() {
		position.origin();
		offset.origin();
	}

};

#endif
