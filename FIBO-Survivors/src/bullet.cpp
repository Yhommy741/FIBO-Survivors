#include "bullet.h"
#include <cmath>

Bullet::Bullet(const std::filesystem::path& exeDir, const sf::Vector2f& startPos, const sf::Vector2f& direction)
    : Entity("Bullet.png", exeDir, 6) 
{
    frameWidth = 32;
    frameHeight = 32;

    sf::Vector2f dir = direction;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0) dir /= len;

    velocity = dir * 600.f;

    sf::Angle rotationAngle = sf::radians(std::atan2(dir.y, dir.x));

    if (sprite) {
        sprite->setPosition(startPos);
        sprite->setScale({ 2.f, 2.f });
        sprite->setRotation(rotationAngle);
    }
}

void Bullet::update(float deltaTime) {
    if (sprite) {
        sprite->move(velocity * deltaTime);
        animate(deltaTime);
        aliveTime += deltaTime;
    }
}

bool Bullet::isDead() const {
    return aliveTime > lifeTime;
}



