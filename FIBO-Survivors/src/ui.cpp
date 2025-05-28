#include "ui.h"

UI::UI(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames)
    : exeDir(exeDir_), fileName(fileName_), totalFrames(numFrames) {
    initialize();
}

void UI::initialize() {
    load();
}

void UI::load() {
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "UI" / "GameOver" / fileName;
    assetPath = std::filesystem::weakly_canonical(assetPath);

    if (!texture.loadFromFile(assetPath.string())) {
        std::cerr << "Failed to load texture\n";
        return;
    }

    sprite = sf::Sprite(texture);
    sprite->setScale({ 2.f, 2.f });
	sprite->setOrigin({ 246.f, 176.f });
    sprite->setPosition({ 800.f, 440.f });
}

void UI::draw(sf::RenderWindow& window) {
    if (sprite) {
        window.draw(*sprite);
    }
}

sf::Vector2f UI::getPosition() {
    if (sprite.has_value()) {
        return sprite->getPosition();
    }
    return { 0.f, 0.f };
}