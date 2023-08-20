#pragma once
#include<SDL.h>
#include<iostream>
#include<string>
#include<vector>

#include<utils/glm/vec2.hpp>

#include"AssetLoader.h"
#include"gameObjects/Player.h"

class Player;

static class Game
{
public:
	static bool gameShouldClose;
	static bool debugMode;

	static std::vector<std::string> map;
	static const char MP_AIR = '0';
	static const char MP_WALL = '#';
	static const char MP_PLAYER = 'P';

	static Player* player;

	static int time;
	static float deltaTime;
	static float normTime;
	static int fps;

	static void init();
	static void handleEvents();
	static void update();
	static void close();

	static char getMapTile(std::vector<std::string> m, glm::ivec2 pos);

private:
	static float prevFrameTime;
};

