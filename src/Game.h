#pragma once
#include<SDL.h>
#include<iostream>

static class Game
{
public:
	static bool gameShouldClose;

	static char* map;

	static int time;
	static float deltaTime;
	static float normTime;

	static void init();
	static void handleEvents();
	static void update();
	static void close();

private:
	static float prevFrameTime;
};

