#pragma once
#include"utils/glm/vec2.hpp"

#include"Game.h"
#include"utils/Debug.h"

using namespace glm;

class Game;

class Player
{
public:
	vec2 startPosition;
	vec2 position;
	vec2 direction;
	float movementSpeed = 2;
	float rotationSpeed = 4;
	float rotationAngleRad = 0;

	bool keyW = false;
	bool keyA = false;
	bool keyS = false;
	bool keyD = false;

	Player();

	void update();
	void inputEvents();

	void move(vec2 velocity);
	void rotate(float angleRad); // 1 left; -1 right;

	vec2 getMapPosition(std::vector<std::string> map);
};

