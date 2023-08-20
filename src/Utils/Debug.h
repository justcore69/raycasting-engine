#pragma once
#include<string>
#include<iostream>

#include"glm/vec2.hpp"
#include"glm/vec3.hpp"

#include "Game.h"

using namespace glm;

static class Debug
{
public:
	static void printVector(std::string name, vec2 vec, bool endl);
	static void printVector(std::string name, vec3 vec, bool endl);
	static void printFPS(bool endl);
	static void print(std::string message);
};

