#pragma once
#include<SDL.h>
#include<iostream>

#include"Game.h"
#include"GameObjects/TestDot.h"

using namespace glm;

static class Render
{
public:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static bool init();
	static void render();
	static void destroy();

	static TestDot* dot;
};

