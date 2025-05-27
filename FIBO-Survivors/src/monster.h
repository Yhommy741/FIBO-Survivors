#pragma once

#include "entity.h"
#include <SFML/System/Vector2.hpp>
#include <cmath> // For std::sqrt

class Monster : public Entity {
private:

public:
    Monster(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames);

    void load() override;
    void randomSpawn(const sf::Vector2f& playerPos, float spawnRadius = 600.f);
    void moveToward(const sf::Vector2f& target, float speed = 2.f);
    sf::Vector2f getPosition();
};
