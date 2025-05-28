#pragma once

#include "entity.h"
#include <SFML/System/Vector2.hpp>

// Bullet class Is derived from Entity and represents a bullet in the game.
class Bullet : public Entity
{
private:
    sf::Vector2f velocity;
    float lifeTime = 2.0f;
    float aliveTime = 0.0f;

public:
	// Constructor that initializes the bullet with a position and direction.
    Bullet(const std::filesystem::path& exeDir, const sf::Vector2f& startPos, const sf::Vector2f& direction);

	// Update animation and position of the bullet based on delta time.
    void update(float deltaTime);

	// Check if the bullet is still alive based on its lifetime.
    bool isDead() const;
};
