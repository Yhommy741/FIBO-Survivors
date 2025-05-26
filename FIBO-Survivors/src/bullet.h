#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(
        const sf::Texture& texture,
        const sf::Vector2f& startPos,
        const sf::Vector2f& targetPos,
        float speed,
        float baseDamage,
        float damageModifier = 0.0f,
        bool isSkillBullet = false
    );
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    bool isAlive() const;
    sf::FloatRect getHitbox() const;
    bool isSkill() const;

    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    float damage;
    float distanceTraveled;
    int animationFrame;
    float animationTimer;
    bool isSkillBullet;
};
