#ifndef SRC_TIME_H_
#define SRC_TIME_H_

#include "SDL.h"

class Time {
public:
	const static int SECOND = 1000;

	static Uint32 getTime();
	static double getDelta();
	static void setDelay(float ms);
	static void setDelta(double delta);

private:
	static float delta;
};

float Time:: delta = 0.0f;

Uint32 Time::getTime() {
	return (SDL_GetTicks());
}

double Time::getDelta() {
	return delta;
}

void Time::setDelta(double delta) {
	Time::delta = delta;
}

void Time:: setDelay(float ms) {
	SDL_Delay(ms);
}

#endif


