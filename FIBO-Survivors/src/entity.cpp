#include "entity.h"

Entity::Entity(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames)
    : exeDir(exeDir_), fileName(fileName_), totalFrames(numFrames) {
    initialize();
}

void Entity::initialize() {
    load(); 
}

void Entity::load() {
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "entity" / "player" / fileName;
    assetPath = std::filesystem::weakly_canonical(assetPath);

    if (!texture.loadFromFile(assetPath.string())) {
        std::cerr << "Failed to load texture\n";
        return;
    }

    // Create the sprite and set its properties
    sprite = sf::Sprite(texture);
    animationFrame = sf::IntRect({ 0, 0 }, { frameWidth, frameHeight });
    sprite->setTextureRect(animationFrame);
    sprite->setOrigin({ frameWidth / 2.f, frameHeight / 2.f });
    sprite->setScale({ 5.f, 5.f });
    sprite->setPosition({ 960.f, 540.f });
}

void Entity::animate(float deltaTime) {
    if (!sprite.has_value()) return; // Check if sprite is initialized

    elapsedTime += deltaTime;

    if (elapsedTime >= frameDuration) {
        elapsedTime -= frameDuration;

        // Move to the next frame
        animationFrame.position.x += frameWidth;
        if (animationFrame.position.x >= frameWidth * totalFrames) {
            animationFrame.position.x = 0; // Loop back to the first frame
        }

        // Update the sprite's texture rectangle
        sprite->setTextureRect(animationFrame);
    }
}

void Entity::draw(sf::RenderWindow& window) {
    if (sprite) { // Only draw if sprite is initialized
        window.draw(*sprite);
    }
}
