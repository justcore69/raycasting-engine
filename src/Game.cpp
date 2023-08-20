#include "Game.h"

bool Game::gameShouldClose = false;
bool Game::debugMode = true;

std::vector<std::string> Game::map = {};

Player* Game::player = nullptr;

// Time
int Game::time = 0;
float Game::deltaTime = SDL_GetTicks();
float Game::prevFrameTime = 0;
float Game::normTime = 0;
int Game::fps = 0;

void Game::init() {

    map = AssetLoader::loadMap("assets/test_map.txt");

    player = new Player();
    player->startPosition = player->getMapPosition(map);
    player->position = player->startPosition;

    std::cout << "Game initialized.\n";
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameShouldClose = true;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_w:
                player->keyW = true;
                break;
            case SDLK_a:
                player->keyA = true;
                break;
            case SDLK_s:
                player->keyS = true;
                break;
            case SDLK_d:
                player->keyD = true;
                break;
            case SDLK_ESCAPE:
                gameShouldClose = true;
                break;
            }
        }
        else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
            case SDLK_w:
                player->keyW = false;
                break;
            case SDLK_a:
                player->keyA = false;
                break;
            case SDLK_s:
                player->keyS = false;
                break;
            case SDLK_d:
                player->keyD = false;
                break;
            }
        }
    }
}

void Game::update() {
    // Time handling
    Uint32 currentFrameTime = SDL_GetTicks();
    deltaTime = (currentFrameTime - prevFrameTime) / 1000.0f; // Convert to seconds
    prevFrameTime = currentFrameTime;
    fps = 1 / deltaTime;

    time++;
    normTime += deltaTime;

    //Debug::printFPS(true);

    player->update();

}

void Game::close() {
    std::cout << "Game closed.\n";
}

char Game::getMapTile(std::vector<std::string> m, ivec2 pos)
{
    if (pos.y >= m.size() || pos.x >= m[0].size()) return '.';
    return m[pos.y][pos.x];
}
