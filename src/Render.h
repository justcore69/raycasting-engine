#pragma once
#include<SDL.h>
#include<iostream>

#include"utils/Debug.h"
#include"utils/Color.h"
#include"Game.h"

#include"gameObjects/Player.h"

using namespace glm;

static class Render
{
public:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

	static float fov;
	static int dof;

	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static bool init();
	static void renderEverything();
	static void renderScene();
	static void renderUI();
	static void destroy();

	static void drawWallLine(float height, float screenPosX, Color color);
	static void drawWalls(Player player);

	static void drawCircle(int centerX, int centerY, int radius);

	static void drawPreview();

	static std::vector<vec2> getRayIntersections(float x1, float y1, float x2, float y2);

	static vec2 normalize(const vec2& v);
	static float magnitude(const vec2& v);
	static float dot(const vec2& v, const vec2& v2);
	static float projection(const vec2& projector, const vec2& floor);
};

