#pragma once
#include <SFML/Graphics.hpp>

class Monster {
public:
    Monster(const sf::Texture& texture, const sf::Vector2f& startPos);
    void update(float dt, const sf::Vector2f& playerPos);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getHitbox() const;
    bool checkPlayerCollision(const sf::FloatRect& playerBounds);
    bool checkBulletCollision(const sf::FloatRect& bulletBounds);
    void onHitPlayer();
    void onHitByBullet();
    bool isDead() const;

private:
    sf::Sprite sprite;
    sf::Vector2f position;
    int hitCount;
    float highlightTimer;
    bool dead;
    float deathTimer;
    int animFrame;
    float animTimer;
};
