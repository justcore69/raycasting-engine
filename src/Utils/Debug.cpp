#include "Debug.h"

void Debug::printVector(std::string name, vec2 vec, bool endl)
{
	if (endl) {
		std::cout << name << ": vec2(" << vec.x << ", " << vec.y << ");\n";
	}
	else {
		std::cout << name << ": vec2(" << vec.x << ", " << vec.y << "); ";
	}
}

void Debug::printVector(std::string name, vec3 vec, bool endl)
{
	if (endl) {
		std::cout << name << ": vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ");\n";
	}
	else {
		std::cout << name << ": vec3(" << vec.x << ", " << vec.y << ", " << vec.z << "); ";
	}
}

void Debug::printFPS(bool endl) {
	endl ? std::cout << "FPS: " << Game::fps << '\n' : std::cout << "FPS: " << Game::fps << "; ";
}

void Debug::print(std::string message) {
	std::cout << message << '\n';
}
