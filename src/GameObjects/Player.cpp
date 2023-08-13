#include "Player.h"

Player::Player()
{
    rotationAngleRad = 0 * (M_PI / 180);
    direction = vec2(1, 0);
}

void Player::move(vec2 velocity) {
    position += velocity;
}

void Player::rotate(float angleRad) {
    rotationAngleRad += angleRad;
}

vec2 Player::getMapPosition(std::vector<std::string> map) {
	if (Game::map[0] == "") {
		std::cerr << "Failed to get player position on the map. Map is NULL or starts with an empty line\n";
	}
    for (int y = 0; y < Game::map.size(); y++) {
        for (int x = 0; x < Game::map[y].size(); x++) {
            if (Game::map[y][x] == 'P') {
                std::cout << "Player position on the map is vec(" << x << ", " << y << ");\n";
                return vec2(x + 0.5f, y + 0.5f);
            }
        }
    }
}
