#include "Game.h"
#include "../TextureManager.h"
#include "../tilemap/TileMap.h"
#include "../AssetsManager.h"
#include "../ECS/Components.h"


/////////////////////////////////////Group Labels////////////////////////////////////
enum groupLabels : std::size_t {
	mapsGroup,
	bgGroup,
	playersGroup,
	enemiesGroup,
	collidersGroup
};


////////////////////////////////Static Member Declaration///////////////////////////
bool Game::isRunning = false;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;



////////////////////////////Manager and Objects Declaration/////////////////////////
Manager manager;
TileMap tileMap;

auto& player = manager.addEntity();



/////////////////////////Get  Vector Reference to the Group/////////////////////
auto& backgrounds(manager.getGroup(bgGroup));
auto& players(manager.getGroup(playersGroup));



//////////////////////////Member Function Declaration///////////////////////////
Game::Game(const char* title, int windowXPos, int windowYPos, bool fullScreen) {

	int flag = 0;

		if(fullScreen) {
			flag = SDL_WINDOW_FULLSCREEN;
		}

		if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
			std::cout << "SDL_INITIALIZED" <<std::endl;

			window = SDL_CreateWindow(title, windowXPos, windowYPos,
					WINDOWWIDTH, WINDOWHEIGHT, flag);
			if(window) {
				std::cout << "WINDOW CREATED" <<std::endl;
			}

			renderer = SDL_CreateRenderer(window, -1, 0);
			if(renderer) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				std::cout << "RENDERER CREATED" << std::endl;
			}

			isRunning = true;
		} else {
			isRunning = false;
			std::cerr << "SDL_NOT_INITIALIZED" << std::endl;
		}

		//load the textures
		AssetsManager::getInstance().LoadTexture();

		//initialize the tileMap
		tileMap.init();
		tileMap.loadMap("assets/maps/Levels/testlvl.txt");
		tileMap.loadTileset(10, 6);

		//player
		player.addComponent<TransformComponent>(0.0f, 5.0f, 1.0f);
		player.addComponent<SpriteComponent>("sPlayer", true);
		player.addComponent<KeyboardController>();
		player.addGroup(playersGroup);

}


void Game::_handleEvents() {
	SDL_PollEvent(&event);

	switch(event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::_update() {

	manager.refresh();
	manager.update();

	tileMap.setPosition(player.getComponent<TransformComponent>().position);
	tileMap.updateMap();

}

void Game::_render() {
	SDL_RenderClear(renderer);

	//draw Background

	TextureManager::getInstance().Draw(AssetsManager::getInstance().getTexture("sBg1"), {0,0,800,640}, SDL_FLIP_NONE);
	TextureManager::getInstance().Draw(AssetsManager::getInstance().getTexture("sBg2"), {0,0,800,640}, SDL_FLIP_NONE);
	TextureManager::getInstance().Draw(AssetsManager::getInstance().getTexture("sBg3"), {0,0,800,640}, SDL_FLIP_NONE);
	TextureManager::getInstance().Draw(AssetsManager::getInstance().getTexture("sBg4"), {0,0,800,640}, SDL_FLIP_NONE);
	TextureManager::getInstance().Draw(AssetsManager::getInstance().getTexture("sBg5"), {0,0,800,640}, SDL_FLIP_NONE);

	//draw map
	tileMap.drawMap();

	//draw rectangle around player
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &player.getComponent<SpriteComponent>().destRect);
	SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);

	//draw player
	for(auto* p:players) {
		p->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::_clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "RESOURCE CLEARED" << std::endl;
}

Game::~Game() {}
