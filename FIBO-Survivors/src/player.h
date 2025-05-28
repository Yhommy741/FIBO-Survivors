#pragma once

#include "entity.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>

// Player class Is derived from Entity and represents a Player in the game.
class Player : public Entity {
private:

    // Set Max Hp
    int hp = 11;

public:

    // Constructor that initializes the Monster
    Player(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames);

    // Player Movement Control
    void move(bool up, bool down, bool left, bool right);

    // Decrease Player Hp
    void decreaseHp(int amount) { hp = std::max(0, hp - amount); }

    // Getter Current Player Hp
    int getHp() const { return hp; }
    
};