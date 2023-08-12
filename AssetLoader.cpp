#include "AssetLoader.h"

std::vector<std::string> AssetLoader::loadMap(std::string path)
{
	std::vector<std::string> map;
	std::ifstream fileStream(path, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "ERROR: Could not read file " << path << ". File does not exist.\n";
		return map;
	}

	std::string line = "";

	int i = 0;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		map[i] = line;
		i++;
	}

	fileStream.close();
	return map;
}
