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

	static std::vector<vec2> getPointsDDA(const float x1, const float y1, const float x2, const float y2);
};

