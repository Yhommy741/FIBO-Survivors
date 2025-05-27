#include "entity.h"

Entity::Entity(std::string fileName_, const std::filesystem::path& exeDir_)
    : exeDir(exeDir_), fileName(fileName_) {  // Removed explicit sprite() initialization
    initialize();
}

void Entity::initialize() {
    load();  // Load once
}

void Entity::load() {
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "entity" / "player" / fileName;
    assetPath = std::filesystem::weakly_canonical(assetPath);

    if (!texture.loadFromFile(assetPath.string())) {
        std::cerr << "Failed to load texture\n";
        return;
    }
    sprite = sf::Sprite(texture);  // construct with texture

    sprite->setTextureRect(sf::IntRect({ 0, 0 }, { 32, 32 }));
    sprite->setOrigin({ 16.f, 16.f });
    sprite->setScale({ 5.f, 5.f });
    sprite->setPosition({ 960.f, 540.f });
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(*sprite);
}