#include "hpbar.h"

HpBar::HpBar(std::string fileName, const std::filesystem::path& exeDir, int numFrames)
    : exeDir(exeDir), fileName(fileName), totalFrames(numFrames)
{
    initialize();
}

void HpBar::initialize() {
    load();
}

void HpBar::load() {
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "UI" / "HP" / fileName;
    assetPath = std::filesystem::weakly_canonical(assetPath);

    if (!texture.loadFromFile(assetPath.string())) {
        std::cerr << "Failed to load texture\n";
        return;
    }

    sprite = sf::Sprite(texture);
    animationFrame = sf::IntRect({ 704, 0 }, { frameWidth, frameHeight });
    sprite->setTextureRect(animationFrame);
    sprite->setOrigin({ frameWidth / 2.f, frameHeight / 2.f });
    sprite->setScale({ 2.f, 2.f });
    sprite->setPosition({ 950.f, 430.f });
    float MaxHP = 0;
}

void HpBar::animate(int currrntHp) {
    if (!sprite.has_value()) return;

    animationFrame.position.x = currrntHp * frameWidth;

    sprite->setTextureRect(animationFrame);

}

void HpBar::draw(sf::RenderWindow& window) {
    if (sprite) {
        window.draw(*sprite);
    }
}


void HpBar::update(sf::Vector2f playerPosition) {
    float offsetY = 120.f;
    sf::Vector2f hpBarPosition = playerPosition - sf::Vector2f(5.f, offsetY);
    sprite->setPosition(hpBarPosition);
}
