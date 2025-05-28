#pragma once

#include "entity.h"
#include <SFML/System/Vector2.hpp>

class Bullet : public Entity
{
private:
    sf::Vector2f velocity;
    float lifeTime = 2.0f;
    float aliveTime = 0.0f;

public:
    Bullet(const std::filesystem::path& exeDir, const sf::Vector2f& startPos, const sf::Vector2f& direction);

    void update(float deltaTime);
    bool isDead() const;
    void setAnimationFrame(int frameIndex);

    sf::Vector2f getPosition() const;
};
