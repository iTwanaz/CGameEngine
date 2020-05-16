#ifndef SRC_ECS_ANIMATION_H_
#define SRC_ECS_ANIMATION_H_

struct Animation {
	int index;
	int frames;
	int speed;

	Animation() = default;

	Animation(int mIndex, int nFrames, int mSpeed) :
		index(mIndex), frames(nFrames), speed(mSpeed){}
};


#endif
