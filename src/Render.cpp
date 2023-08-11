#include "Render.h"

SDL_Window* Render::window = NULL;
SDL_Renderer* Render::renderer = NULL;

TestDot* Render::dot = new TestDot(Vec2(SCREEN_WIDTH, SCREEN_HEIGHT), Color::black);

bool Render::init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL not initialized. SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    renderer = SDL_CreateRenderer(window, -1, 0);

    std::cout << "Render initialized.\n";

    return true;
}

void Render::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    dot->position = Vec2(SCREEN_WIDTH/2 + sinf(Game::normTime) * 64, SCREEN_HEIGHT/2 + cosf(Game::normTime) * 64);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, dot->position.X, dot->position.Y);

    SDL_RenderPresent(renderer);
}

void Render::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Render destroyed. SDL_Quit()\n";
}
