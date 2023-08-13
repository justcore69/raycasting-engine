#include "Color.h"

Color const Color::white = Color(255, 255, 255);
Color const Color::black = Color(0, 0, 0);
Color const Color::gray = Color(64, 64, 64);
Color const Color::red = Color(255, 0, 0);
Color const Color::green = Color(0, 255, 0);
Color const Color::blue = Color(0, 0, 255);
Color const Color::yellow = Color(255, 255, 0);
Color const Color::magnelia = Color(255, 0, 255);

Color::Color(uint8_t r, uint8_t g, uint8_t b)
{
	R = r;
	G = g;
	B = b;
	A = 255;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}
