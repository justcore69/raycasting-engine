#include "Render.h"

float Render::fov = 0;
int Render::dof = 0;

SDL_Window* Render::window = NULL;
SDL_Renderer* Render::renderer = NULL;

bool Render::init()
{
    fov = 70 * (M_PI / 180);
    dof = 10;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL not initialized. SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Raycasting Engine with SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
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
    // Render sky
    SDL_SetRenderDrawColor(renderer, 6, 10, 19, 255);

    SDL_Rect skyRect;
    skyRect.x = 0;
    skyRect.y = 0;
    skyRect.w = SCREEN_WIDTH;
    skyRect.h = SCREEN_HEIGHT;
    SDL_RenderFillRect(renderer, &skyRect);

    // Render floor

    for (int y = SCREEN_HEIGHT/2; y < SCREEN_HEIGHT; y+=SCREEN_DIVIDER) {
        float divider = static_cast<int>(SCREEN_HEIGHT + 64 - y) / 15;
        if (divider < 1) divider = 1;

        SDL_SetRenderDrawColor(renderer, 134 / divider, 80 / divider, 36 / divider, 255);

        SDL_Rect rect;
        rect.x = 0;
        rect.y = y;
        rect.w = SCREEN_WIDTH;
        rect.h = SCREEN_DIVIDER;

        SDL_RenderFillRect(renderer, &rect);
    }

    // Render walls
    rayDistances.clear();
    for (int i = 0; i < RAYS_COUNT; i++) {
        float step = fov / RAYS_COUNT;

        vec2 ray = vec2(Game::player->position.x + 1 * cosf(Game::player->rotationAngleRad + (step * i) - fov / 2),
            Game::player->position.y + 1 * -sinf(Game::player->rotationAngleRad + (step * i) - fov / 2));

        float dist = castRay(Game::player->position.x, Game::player->position.y, ray.x, ray.y);
        rayDistances.push_back(dist);
        
        // Fish eye fix
        float rayAngle = atan2f(ray.y - Game::player->position.y, ray.x - Game::player->position.x);
        float playerAngle = atan2f(Game::player->direction.y, Game::player->direction.x);
        dist *= cosf(rayAngle - playerAngle);

        if (dist < 1) dist = 1;
        float height = SCREEN_HEIGHT / dist;

        Color wallColor = Color(128 / (dist * dist), 128 / (dist * dist), 128 / (dist * dist));

        if (!isnan(dist)) {
            for (int j = 0; j < SCREEN_DIVIDER; j++) {
                drawWallLine(height, SCREEN_WIDTH - j - i * SCREEN_DIVIDER, wallColor);
            }
        }
        else {
            
        }

    }
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

void Render::drawWallLine(float height, int screenPosX, Color color) {
    SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
    SDL_RenderDrawLineF(renderer, screenPosX, SCREEN_HEIGHT/2 - height/2, screenPosX, SCREEN_HEIGHT / 2 + height / 2);
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

            if (Game::map[y][x] == Game::MP_WALL) { // Draw wall
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
    for (int i = 0; i < RAYS_COUNT; i++) {
        float step = fov / RAYS_COUNT;

        vec2 ray = vec2(playerScrPos.x + 1 * cosf(Game::player->rotationAngleRad + (step * i) - fov/2),
            playerScrPos.y + 1 * -sinf(Game::player->rotationAngleRad + (step * i) - fov/2));

        //std::cout << rayDistances.size() << '\n';
        float dist = rayDistances[i == 0 ? i : i - 1];

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        if (!isnan(dist)) {
            SDL_RenderDrawLineF(renderer, playerScrPos.x, playerScrPos.y,
                (ray.x - playerScrPos.x) * dist * cellSize + playerScrPos.x,
                (ray.y - playerScrPos.y) * dist * cellSize + playerScrPos.y);
        }
        else {
            SDL_RenderDrawLineF(renderer, playerScrPos.x, playerScrPos.y,
                (ray.x - playerScrPos.x) * 128 + playerScrPos.x, 
                (ray.y - playerScrPos.y) * 128 + playerScrPos.y);
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

std::vector<float> Render::rayDistances = {};
float Render::castRay(float x1, float y1, float x2, float y2) {
    // Setup
    float dist = std::numeric_limits<float>::max();

    float dx = x2 - x1;
    float dy = y2 - y1;

    float m = 0;
    if(dx != 0) m = dy / dx;

    vec2 dir = normalize(vec2(dx, dy));
    float angle = atan2f(dir.y, dir.x);

    bool right;
    bool down;

    ivec2 dirRound = ivec2(ceil(dir.x), ceil(dir.y));
    right = dirRound.x == 1;
    down = dirRound.y == 1;

    // Vertical lines handling
    float firstX = right ? ceil(x1) : floor(x1);
    float firstY = y1 + (firstX - x1) * m;

    float x = firstX;
    float y = firstY;

    for (int i = 0; i < dof; i++) {
        float mapX = static_cast<int>(x);
        float mapY = static_cast<int>(y);

        if (!right) mapX -= 1;

        if (Game::getMapTile(Game::map, ivec2(mapX, mapY)) == Game::MP_WALL) {
            dist = distance(vec2(x1, y1), vec2(x, y));
            break;
        }

        x += right ? 1 : -1;
        y += right ? m : -m;
    }

    // Horizontal lines handling
    if (dx != 0) m = dx / dy;

    firstY = down ? ceil(y1) : floor(y1);
    firstX = x1 + (firstY - y1) * m;

    x = firstX;
    y = firstY;

    for (int i = 0; i < dof; i++) {
        float mapX = static_cast<int>(x);
        float mapY = static_cast<int>(y);

        if (!down) mapY -= 1;

        if (Game::getMapTile(Game::map, ivec2(mapX, mapY)) == Game::MP_WALL) {            
            float newDist = distance(vec2(x1, y1), vec2(x, y));
            if (newDist < dist) { 
                dist = distance(vec2(x1, y1), vec2(x, y)); 
                break;
            }
        }

        x += down ? m : -m;
        y += down ? 1 : -1;
    }

    if (dist == std::numeric_limits<float>::max()) dist = std::numeric_limits<float>::quiet_NaN();
    return dist;
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

float Render::dot(const vec2& v1, const vec2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float Render::distance(const vec2& v1, const vec2& v2) {
    return sqrt(fabs(v2.x - v1.x) * fabs(v2.x - v1.x) + fabs(v2.y - v1.y) * fabs(v2.y - v1.y));
}