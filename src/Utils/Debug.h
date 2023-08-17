#pragma once
#include"glm/vec2.hpp"
#include"glm/vec3.hpp"
#include<string>
#include<iostream>

using namespace glm;

static class Debug
{
public:
	static void printVector(std::string name, vec2 vec, bool endl);
	static void printVector(std::string name, vec3 vec, bool endl);
	static void print(std::string message);
};

