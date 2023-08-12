#include "Game.h"

bool Game::gameShouldClose = false;

// Time
int Game::time = 0;
float Game::deltaTime = SDL_GetTicks();
float Game::prevFrameTime = 0;
float Game::normTime = 0;

void Game::init() {
	std::cout << "Game initialized.\n";
}

void Game::handleEvents() {
	SDL_Event e;
	SDL_PollEvent(&e);

    if (e.type == SDL_QUIT) {
        gameShouldClose = true;
    }
    else if (e.type == SDL_KEYDOWN) {
        // Handle key presses
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
            gameShouldClose = true;
            break;
        case SDLK_SPACE:
            // Handle space key press
            break;
            // Add more cases for other keys as needed
        }
    }
}

void Game::update() {
	// Time handling
	Uint32 currentFrameTime = SDL_GetTicks();
	deltaTime = (currentFrameTime - prevFrameTime) / 1000.0f; // Convert to seconds
	prevFrameTime = currentFrameTime;

	time++;
	normTime += deltaTime;

	std::cout << "normTime: " << normTime << "; deltaTime: " << deltaTime << '\n';
}

void Game::close() {
	std::cout << "Game closed.\n";
}