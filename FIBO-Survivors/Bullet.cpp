#include "Bullet.h"
#include <cmath>

Bullet::Bullet(
    const sf::Texture& texture,
    const sf::Vector2f& startPos,
    const sf::Vector2f& targetPos,
    float speed,
    float baseDamage,
    float damageModifier
)
    : position(startPos),
    speed(speed),
    damage(baseDamage + damageModifier),
    distanceTraveled(0.0f),
    animationFrame(0),
    animationTimer(0.0f)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));
    sprite.setOrigin({ 8.f, 8.f });
    sprite.setPosition(position);

    sf::Vector2f dir = targetPos - startPos;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0)
        direction = dir / len;
    else
        direction = { 1.f, 0.f };
}

void Bullet::update(float dt) {
    sf::Vector2f move = direction * speed * dt;
    position += move;
    distanceTraveled += std::sqrt(move.x * move.x + move.y * move.y);
    sprite.setPosition(position);

    animationTimer += dt;
    if (animationTimer > 0.08f) {
        animationFrame = (animationFrame + 1) % 4;
        sprite.setTextureRect(sf::IntRect({ animationFrame * 16, 0 }, { 16, 16 }));
        animationTimer = 0.0f;
    }
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Bullet::isAlive() const {
    return distanceTraveled < 1000.f;
}

float Bullet::getDamage() const {
    return damage;
}
