#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 640

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class Game {
private:
	SDL_Window* window;

public:
	static bool isRunning;
	static SDL_Renderer* renderer;
	static SDL_Event event;

	Game(const char* title, int windowXPos, int windowYPos, bool fullScreen);
	~Game();
	void _handleEvents();
	void _update();
	void _render();
	void _clean();

	inline bool _running() { return isRunning; }
};

#endif
