#pragma once
#include"utils/glm/vec2.hpp"

using namespace glm;

class Player
{
public:
	vec2 position;
	vec2 direction;

	Player(vec2 pos, vec2 dir);
};

