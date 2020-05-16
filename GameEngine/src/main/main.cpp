#include "Time.h"
#include "Game.h"

Game* game = nullptr;

const float FPS = 60.0;
const float targetTime = 1.0 / FPS;

int main(int argc, char* argv[]) {

	int frames = 0;
	long frameCounter = 0;

	Uint32 lastTime = Time::getTime();
	double unprocessedTime = 0;

	game = new Game("Game_test_1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);

	while(game->isRunning) {

		bool render = false;

		Uint32 startTime = Time::getTime();
		Uint32 passedTime = startTime - lastTime;
		lastTime = startTime;

		unprocessedTime += passedTime / (double)Time::SECOND;
		frameCounter += passedTime;

		while(unprocessedTime > targetTime) {
			render = true;

			unprocessedTime -= targetTime;

			game->_handleEvents();
			game->_update();

			if(frameCounter >= Time::SECOND) {
//				std::cout << frames << std::endl;
				frames = 0;
				frameCounter = 0;
			}

		}

		if(render) {
			game->_render();
			frames++;
		} else {
			Time::setDelay(1.0f);
		}

	}

	game->_clean();
	return 0;
}
