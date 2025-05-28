#pragma once

#include "entity.h"
#include <SFML/System/Vector2.hpp>
#include <cmath> // For std::sqrt

class Player : public Entity {
private:
    int hp = 11;
public:
    Player(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames);

    void move(bool up, bool down, bool left, bool right);
    void decreaseHp(int amount) { hp = std::max(0, hp - amount); }
    int getHp() const { return hp; }
    
};