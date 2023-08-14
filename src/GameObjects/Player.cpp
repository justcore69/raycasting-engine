#include "Player.h"

Player::Player()
{
    rotationAngleRad = 0 * (M_PI / 180);
    direction = vec2(1, 0);
}

void Player::update() {
    //position.y = startPosition.y + cosf(Game::normTime);
    //rotate(M_PI / 180);

    direction = vec2(cosf(rotationAngleRad), sinf(-rotationAngleRad));
    inputEvents();
}

void Player::inputEvents() {
    // Movement

    std::cout << keyW << keyA << keyS << keyD << '\n';
    Debug::printVector("dir", direction);

    if (keyW) { // Forward
        move(direction * movementSpeed);
    }
    if (keyA) { // Rotate left
        rotate(rotationSpeed);
    }
    if (keyS) { // Backward
        move(-direction * movementSpeed);
    }
    if (keyD) { // Rotate right
        rotate(-rotationSpeed);
    }
}

void Player::move(vec2 velocity) {
    position += velocity * Game::deltaTime;
}

void Player::rotate(float angleRad) {
    rotationAngleRad += angleRad * Game::deltaTime;;
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
