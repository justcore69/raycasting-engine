#pragma once
#include<SDL.h>
#include<iostream>
#include<string>
#include<vector>

#include"AssetLoader.h"
#include"gameObjects/Player.h"

class Player;

static class Game
{
public:
	static bool gameShouldClose;
	static bool debugMode;

	static std::vector<std::string> map;

	static Player* player;

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

