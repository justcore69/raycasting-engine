#pragma once
#include<SDL.h>
#include<iostream>

#include"Game.h"
#include"GameObjects/TestDot.h"

#include"gameObjects/Player.h"

using namespace glm;

static class Render
{
public:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

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

	static TestDot* dot;
};

