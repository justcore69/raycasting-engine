#pragma once
#include"Utils/Vec2.h"
#include"Utils/Color.h"

class TestDot
{
public:
	Vec2 position = Vec2(0, 0);
	Color color = Color::black;

	TestDot(Vec2 pos, Color col);
};