#include "Monster.h"
#include <cmath>

Monster::Monster(const sf::Texture& texture, const sf::Vector2f& startPos, sf::Vector2i frameSize, int numFrames)
    : sprite(texture), position(startPos), hitCount(0), highlightTimer(0.f), dead(false), deathTimer(0.f),
    animFrame(0), animTimer(0.f), frameSize(frameSize), numFrames(numFrames)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, frameSize));
    sprite.setOrigin({ frameSize.x / 2.f, frameSize.y / 2.f });
    sprite.setPosition(position);
    sprite.setScale({ 4.f, 4.f });
}

void Monster::update(float dt, const sf::Vector2f& playerPos) {
    if (dead) {
        if (deathTimer > 0.f)
            deathTimer -= dt;
        return;
    }
    animTimer += dt;
    if (animTimer > 0.09f) {
        animFrame = (animFrame + 1) % numFrames;
        sprite.setTextureRect(sf::IntRect({ animFrame * frameSize.x, 0 }, frameSize));
        animTimer = 0.f;
    }
    sf::Vector2f dir = playerPos - position;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 1e-2f) {
        dir /= len;
        position += dir * 200.0f * dt;
        sprite.setPosition(position);
    }
    if (highlightTimer > 0.f)
        highlightTimer -= dt;
}

void Monster::draw(sf::RenderWindow& window) const {
    if (dead && deathTimer <= 0.f) return;
    sf::Sprite s = sprite;
    if (highlightTimer > 0.f || (dead && deathTimer > 0.f)) {
        s.setColor(sf::Color(255, 80, 80));
    }
    window.draw(s);
}

sf::FloatRect Monster::getHitbox() const {
    sf::FloatRect box = sprite.getGlobalBounds();
    float shrink = 0.5f;
    box.position.x += box.size.x * shrink / 2.f;
    box.position.y += box.size.y * shrink / 2.f;
    box.size.x *= (1.f - shrink);
    box.size.y *= (1.f - shrink);
    return box;
}

bool Monster::checkPlayerCollision(const sf::FloatRect& playerBounds) {
    return !dead && (
        (getHitbox().position.x < playerBounds.position.x + playerBounds.size.x) &&
        (getHitbox().position.x + getHitbox().size.x > playerBounds.position.x) &&
        (getHitbox().position.y < playerBounds.position.y + playerBounds.size.y) &&
        (getHitbox().position.y + getHitbox().size.y > playerBounds.position.y)
        );
}

bool Monster::checkBulletCollision(const sf::FloatRect& bulletBounds) {
    return !dead && (
        (getHitbox().position.x < bulletBounds.position.x + bulletBounds.size.x) &&
        (getHitbox().position.x + getHitbox().size.x > bulletBounds.position.x) &&
        (getHitbox().position.y < bulletBounds.position.y + bulletBounds.size.y) &&
        (getHitbox().position.y + getHitbox().size.y > bulletBounds.position.y)
        );
}

void Monster::onHitPlayer() {
    hitCount++;
    highlightTimer = 0.2f;
    if (hitCount >= 2) {
        dead = true;
        deathTimer = 0.5f;
    }
}

void Monster::onHitByBullet() {
    if (!dead) {
        dead = true;
        highlightTimer = 0.5f;
        deathTimer = 0.5f;
    }
}

bool Monster::isDead() const { return dead && deathTimer <= 0.f; }
