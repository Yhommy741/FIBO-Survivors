#include "monster.h"
#include <iostream>
#include <random>
#include <cmath>
#include <array>

Monster::Monster(const std::string& fileName, const std::filesystem::path& exeDir, int numFrames)
    : Entity(fileName, exeDir, numFrames)
{
    load();
}

void Monster::load() {
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "entity" / "monster" / fileName;
    assetPath = std::filesystem::weakly_canonical(assetPath);

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

MonsterInfo getRandomMonsterInfo() {
    static const std::array<MonsterInfo, 7> monsterTypes = {{
        {"Sprite-Capa-stand.png", 8},
        {"Sprite-IC-stand.png", 5},
        {"StackOverflow-Sheet.png", 5}
        ,{"Sprite-0002.png", 2},
        {"Sprite-0001.png", 2},
        {"Error-Sheet.png", 5},
        {"Bug-Sheet", 4}
    }};
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, monsterTypes.size() - 1);
    return monsterTypes[dist(gen)];
}