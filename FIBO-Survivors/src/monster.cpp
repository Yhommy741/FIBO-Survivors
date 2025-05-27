#include "monster.h"
#include <iostream>
#include <random>
#include <cmath>

Monster::Monster(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames)
    : Entity(fileName_, exeDir_, numFrames) {
    load();
}

void Monster::load() {
    // ??????? assets/entity/monster/
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "entity" / "monster" / "Sprite-Capa-stand.png";
    assetPath = std::filesystem::weakly_canonical(assetPath);

    std::cout << "Loading monster from: " << assetPath << std::endl;

    if (!texture.loadFromFile(assetPath.string())) {
        std::cerr << "Failed to load monster texture: " << assetPath << std::endl;
        return;
    }
    sprite = sf::Sprite(texture);
    animationFrame = sf::IntRect({ 0, 0 }, { frameWidth, frameHeight });
    sprite->setTextureRect(animationFrame);
    sprite->setOrigin({ frameWidth / 2.f, frameHeight / 2.f });
    sprite->setScale({ 5.f, 5.f });
    sprite->setPosition({ 960.f, 540.f });
}

void Monster::randomSpawn(const sf::Vector2f& playerPos, float spawnRadius) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angleDist(0, 2 * 3.14159265f);

    float angle = angleDist(gen);
    float x = playerPos.x + spawnRadius * std::cos(angle);
    float y = playerPos.y + spawnRadius * std::sin(angle);

    if (sprite.has_value()) {
        sprite->setPosition({ x, y });
    }
}

void Monster::moveToward(const sf::Vector2f& target, float speed) {
    if (!sprite.has_value()) return;
    sf::Vector2f pos = sprite->getPosition();
    sf::Vector2f dir = target - pos;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 1e-2f) {
        dir /= len;
        sprite->setPosition(pos + dir * speed);
    }
}

sf::Vector2f Monster::getPosition() {
    if (sprite.has_value()) return sprite->getPosition();
    return { 0.f, 0.f };
}