#pragma once
#include"utils/glm/vec2.hpp"

#include"Game.h"

using namespace glm;

class Game;

class Player
{
public:
	vec2 position;
	float rotationAngleRad;
	vec2 direction;

	Player();

	void move(vec2 velocity);
	void rotate(float angleRad); // 1 left; -1 right;

	vec2 getMapPosition(std::vector<std::string> map);
};

