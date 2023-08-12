#pragma once
#include"utils/glm/vec2.hpp"
#include"utils/Color.h"

using namespace glm;

class TestDot
{
public:
	vec2 position = vec2(0, 0);
	Color color = Color::black;

	TestDot(vec2 pos, Color col);
};