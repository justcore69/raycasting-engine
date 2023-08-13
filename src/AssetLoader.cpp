#include "AssetLoader.h"

std::vector<std::string> AssetLoader::loadMap(std::string path)
{
	std::vector<std::string> map;
	std::ifstream fileStream(path, std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "ERROR: Could not read file " << path << ". File does not exist.\n";
		return map;
	}

	std::string line = "";

	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		map.push_back(line);
	}

	fileStream.close();

	std::cout << "Map loaded: " << path << '\n';
	
	// Show map
	for (std::string line : map) {
		std::cout << line << '\n';
	}
	std::cout << '\n';

	return map;
}
