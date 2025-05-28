#pragma once

#include "entity.h"
#include <SFML/System/Vector2.hpp>
#include <cmath> // For std::sqrt

struct MonsterInfo {
    std::string fileName;
    int numFrames;
};

MonsterInfo getRandomMonsterInfo();

class Monster : public Entity {
public:
    Monster(const std::string& fileName, const std::filesystem::path& exeDir, int numFrames);

    void randomSpawn(const sf::Vector2f& playerPos, float spawnRadius = 600.f);
    void moveToward(const sf::Vector2f& target, float speed = 2.f);
};
