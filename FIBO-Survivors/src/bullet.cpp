#include "Bullet.h"
#include <cmath>

Bullet::Bullet(
    const sf::Texture& texture,
    const sf::Vector2f& startPos,
    const sf::Vector2f& targetPos,
    float speed,
    float baseDamage,
    float damageModifier,
    bool isSkillBullet
) : sprite(texture),
position(startPos),
speed(speed),
damage(baseDamage + damageModifier),
distanceTraveled(0.0f),
animationFrame(0),
animationTimer(0.0f),
isSkillBullet(isSkillBullet)
{
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));
    sprite.setOrigin({ 8.f, 8.f });
    sprite.setPosition(position);
    sprite.setScale({ 7.f, 7.f });

    sf::Vector2f dir = targetPos - startPos;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0)
        direction = dir / len;
    else
        direction = { 1.f, 0.f };

    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f + 180.f;
    sprite.setRotation(sf::degrees(angle));
}

void Bullet::update(float dt) {
    sf::Vector2f move = direction * speed * dt;
    position += move;
    distanceTraveled += std::sqrt(move.x * move.x + move.y * move.y);
    sprite.setPosition(position);

    animationTimer += dt;
    if (animationTimer > 0.08f) {
        animationFrame = (animationFrame + 1) % 4;
        sprite.setTextureRect(sf::IntRect({ 0, animationFrame * 16 }, { 16, 16 }));
        animationTimer = 0.0f;
    }

    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f + 180.f;
    sprite.setRotation(sf::degrees(angle));
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Bullet::isAlive() const {
    return distanceTraveled < 1000.f;
}

sf::FloatRect Bullet::getHitbox() const {
    sf::FloatRect box = sprite.getGlobalBounds();
    float shrink = 0.4f;
    box.position.x += box.size.x * shrink / 2.f;
    box.position.y += box.size.y * shrink / 2.f;
    box.size.x *= (1.f - shrink);
    box.size.y *= (1.f - shrink);
    return box;
}

bool Bullet::isSkill() const { return isSkillBullet; }
