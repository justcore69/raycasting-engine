#pragma once
#include <cstdint>

class Color
{
public:
	uint8_t R, G, B, A;

	static const Color white;
	static const Color black;
	static const Color red;
	static const Color green;
	static const Color blue;
	static const Color yellow;
	static const Color magnelia;

	Color(uint8_t r, uint8_t g, uint8_t b);
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};

