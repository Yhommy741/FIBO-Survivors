#pragma once

#include "entity.h"
#include <SFML/System/Vector2.hpp>
#include <cmath> // For std::sqrt

class Player : public Entity {
private:

public:
    Player(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames);

    void move(bool up, bool down, bool left, bool right);
    
};