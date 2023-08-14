#include "Debug.h"

void Debug::printVector(std::string name, vec2 vec)
{
	std::cout << name << ": vec2(" << vec.x << ", " << vec.y << ");\n";
}

void Debug::printVector(std::string name, vec3 vec)
{
	std::cout << name << ": vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ");\n";
}

void Debug::print(std::string message) {
	std::cout << message << '\n';
}
