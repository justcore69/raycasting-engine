#include "Game.h"
#include "Render.h"

int main(int argc, char* args[])
{
    // INITIALIZATION //
    Game::init();
    Render::init();

    // MAIN LOOP //
    while (!Game::gameShouldClose) {
        Game::handleEvents();
        Game::update();
        Render::render();
    }

    Render::destroy();
    Game::close();
    return 0;
}