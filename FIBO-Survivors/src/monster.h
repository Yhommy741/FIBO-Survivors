#pragma once

#include "entity.h"
#include <SFML/System/Vector2.hpp>
#include <cmath> // For std::sqrt

// Declare Monster Types
struct MonsterInfo {
    std::string fileName;
    int numFrames;
};

MonsterInfo getRandomMonsterInfo();

// Monster class Is derived from Entity and represents Monsters in the game.
class Monster : public Entity {
public:

    // Constructor that initializes the Monster
    Monster(const std::string& fileName, const std::filesystem::path& exeDir, int numFrames);

    // Function random Spawn Monster around Player for the whole game
    void randomSpawn(const sf::Vector2f& playerPos, float spawnRadius = 600.f);

    // Monster Move Toward to Player
    void moveToward(const sf::Vector2f& target, float speed = 2.f);
};
