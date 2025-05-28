#include "player.h"

Player::Player(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames)
    : Entity(fileName_, exeDir_, numFrames) {
}

void Player::move(bool up, bool down, bool left, bool right) {
    sf::Vector2f direction(0.f, 0.f);

    // Determine movement direction
    if (up) direction.y -= 1.f;
    if (down) direction.y += 1.f;
    if (left) direction.x -= 1.f;
    if (right) direction.x += 1.f;

    // Normalize the direction vector
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude > 0.f) {
        direction.x /= magnitude;
        direction.y /= magnitude;
    }

    if (sprite.has_value()) {
        if (direction.x < 0) {
            sprite->setScale({ -5.f, 5.f });
        }
        else if (direction.x > 0) {
            sprite->setScale({ 5.f, 5.f });
        }

    }

	direction *= 4.f;

    if (sprite.has_value()) {
        sf::Vector2f currentPosition = sprite->getPosition();
        sf::Vector2f newPosition = currentPosition + direction; // No speed, just direction
        sprite->setPosition(newPosition);
    }
}


