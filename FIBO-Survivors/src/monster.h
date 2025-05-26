#pragma once
#include <SFML/Graphics.hpp>

class Monster {
public:
    Monster(const sf::Texture& texture, const sf::Vector2f& startPos, sf::Vector2i frameSize = { 32,32 }, int numFrames = 8);
    void update(float dt, const sf::Vector2f& playerPos);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getHitbox() const;
    bool checkPlayerCollision(const sf::FloatRect& playerBounds);
    bool checkBulletCollision(const sf::FloatRect& bulletBounds);
    void onHitPlayer();
    void onHitByBullet();
    bool isDead() const;

    // (ถ้าต้องการให้เข้าถึง frameSize/numFrames จาก main.cpp)
    sf::Vector2i frameSize;
    int numFrames;
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
