#include "Render.h"

SDL_Window* Render::window = NULL;
SDL_Renderer* Render::renderer = NULL;

TestDot* Render::dot = new TestDot(vec2(SCREEN_WIDTH, SCREEN_HEIGHT), Color::black);

bool Render::init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL not initialized. SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Raycast Engine with SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    renderer = SDL_CreateRenderer(window, -1, 0);

    std::cout << "Render initialized.\n";

    return true;
}

void Render::renderEverything() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render functions go here
    renderScene();
    renderUI();


    SDL_RenderPresent(renderer);
}

void Render::renderScene() {
    //dot->position = vec2(SCREEN_WIDTH/2 + sinf(Game::normTime) * 64, SCREEN_HEIGHT/2 + cosf(Game::normTime) * 64);
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderDrawPoint(renderer, dot->position.x, dot->position.y);

    drawWallLine(powf(cosf(Game::normTime), 2) * SCREEN_HEIGHT, SCREEN_WIDTH / 2, Color::green);
}

void Render::renderUI() {
    if(Game::debugMode) drawPreview();
}

void Render::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Render destroyed. SDL_Quit()\n";
}

void Render::drawWallLine(float height, float screenPosX, Color color) {
    SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
    SDL_RenderDrawLineF(renderer, screenPosX, SCREEN_HEIGHT/2 - height/2, screenPosX, SCREEN_HEIGHT / 2 + height / 2);
}

void Render::drawWalls(Player player) {

}

void Render::drawCircle(int centerX, int centerY, int radius) {
    for (int angle = 0; angle < 360; angle++) {
        double radians = angle * (M_PI / 180.0);
        int x = static_cast<int>(centerX + radius * std::cos(radians));
        int y = static_cast<int>(centerY + radius * std::sin(radians));
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void Render::drawPreview() {
    int cellSize = 16;

    // Draw background
    SDL_Rect backgroundRect;
    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.w = cellSize;
    backgroundRect.h = cellSize;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &backgroundRect);

    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
    SDL_RenderDrawRect(renderer, &backgroundRect);

    // Draw map
    for (int y = 0; y < Game::map.size(); y++) {
        for (int x = 0; x < Game::map[y].size(); x++) {
            SDL_Rect cell;
            cell.x = x * cellSize;
            cell.y = y * cellSize;
            cell.w = cellSize;
            cell.h = cellSize;

            if (Game::map[y][x] == '#') { // Draw wall
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderDrawRect(renderer, &cell);
            }
            else { // Draw air
                SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
                SDL_RenderDrawRect(renderer, &cell);
            }
        }
    }

    // Draw player

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    drawCircle(Game::player->position.x * cellSize, Game::player->position.y * cellSize, cellSize / 2.5f);
    SDL_RenderDrawLine(renderer, 
        Game::player->position.x * cellSize, 
        Game::player->position.y * cellSize, 
        Game::player->position.x * cellSize + cosf(Game::player->rotationAngleRad) * (cellSize / 2.5f),
        Game::player->position.y * cellSize + sinf(-Game::player->rotationAngleRad) * (cellSize / 2.5f));
}