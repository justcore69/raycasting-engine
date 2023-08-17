#include "Render.h"

float Render::fov = 0;
int Render::dof = 0;

SDL_Window* Render::window = NULL;
SDL_Renderer* Render::renderer = NULL;

bool Render::init()
{
    fov = 90 * (M_PI / 180);
    dof = 6;

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
        int x = static_cast<int>(centerX + radius * cosf(radians));
        int y = static_cast<int>(centerY + radius * sinf(radians));
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

    vec2 playerScrPos = vec2(Game::player->position.x * cellSize, Game::player->position.y * cellSize);

    // Draw rays
    for (int i = 1; i < 2; i++) {
        float step = fov / 2;

        vec2 ray = vec2(playerScrPos.x + 64 * cosf(Game::player->rotationAngleRad + (step * i) - fov/2),
            playerScrPos.y + 64 * -sinf(Game::player->rotationAngleRad + (step * i) - fov/2));

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawLineF(renderer, playerScrPos.x, playerScrPos.y, ray.x, ray.y);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        std::vector<vec2> points = getRayIntersections(playerScrPos.x/cellSize, playerScrPos.y / cellSize, ray.x / cellSize, ray.y / cellSize);
        for (vec2 p : points) {
            drawCircle(p.x * cellSize, p.y * cellSize, 1);
        }
    }

    // Draw player

    // circle
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    drawCircle(playerScrPos.x, playerScrPos.y, cellSize / 2.5f);

    // angle
    SDL_RenderDrawLine(renderer,
        playerScrPos.x,
        playerScrPos.y,
        playerScrPos.x + cosf(Game::player->rotationAngleRad) * (cellSize / 2.5f),
        playerScrPos.y + sinf(-Game::player->rotationAngleRad) * (cellSize / 2.5f));
}

std::vector<vec2> Render::getRayIntersections(float x1, float y1, float x2, float y2) {
    std::vector<vec2> points;

    float dx = x2 - x1;
    float dy = y2 - y1;

    float m = 0;
    if(dx != 0) m = dy / dx;

    vec2 dir = normalize(vec2(dx, dy));
    float angle = atan2f(dir.y, dir.x);

    float firstX = 0;
    float firstY = 0;

    // Check the quadrants
    bool right;
    bool down;
    ivec2 dirRound = ivec2(ceil(dir.x), ceil(dir.y));
    right = dirRound.x == 1;
    down = dirRound.y == 1;

    firstX = right ? ceil(x1) : floor(x1);
    firstY = y1 + (firstX - x1) * m;

    Debug::printVector("dirRound", dirRound, false);
    std::cout << "slope: " << m << '\n';
    
    points.emplace_back(firstX, firstY);

    float x = firstX;
    float y = firstY;

    for (int i = 0; i < dof; i++) {
        x += right ? 1 : -1;
        y += right ? m : -m;
        points.emplace_back(x, y);
    }

    return points;
}

vec2 Render::normalize(const vec2& v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y);

    if (length != 0.0f) {
        float invLength = 1.0f / length;
        return vec2(v.x * invLength, v.y * invLength);
    }
    else {
        return vec2(0.0f, 0.0f); // Return a default value for zero vectors
    }
}

float Render::magnitude(const vec2& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

float Render::dot(const vec2& v1, const vec2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float Render::projection(const vec2& projector, const vec2& floor) {
    return dot(projector, floor) / magnitude(floor);
}