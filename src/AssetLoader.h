#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>

static class AssetLoader
{
public:
	static std::vector<std::string> loadMap(std::string path);
};

