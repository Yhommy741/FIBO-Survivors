#include "timer.h"
#include <iostream>

Timer::Timer(const std::string& fileName, const std::filesystem::path& exeDir, int totalFrames)
    : exeDir(exeDir), fileName(fileName), totalFrames(totalFrames), elapsedSeconds(0.f)
{
    initialize();
}

void Timer::initialize() {
    load();

    if (texture.getSize().x == 0) {
        std::cerr << "Texture not loaded properly\n";
        return;
    }

    for (int i = 0; i < 5; ++i) {
        sprites[i].emplace(texture);
        sprites[i]->setOrigin({ frameWidth / 2.f, frameHeight / 2.f });
        sprites[i]->setScale({ 2.f, 2.f });
    }

    float spacing = frameWidth * 2.f * 1.1f;
    sprites[0]->setPosition({ 0.f, 0.f });
    sprites[1]->setPosition({ spacing, 0.f });
    sprites[2]->setPosition({ spacing * 2.f, 0.f });
    sprites[3]->setPosition({ spacing * 3.f, 0.f });
    sprites[4]->setPosition({ spacing * 4.f, 0.f });

}

void Timer::load() {
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "UI" / "Timer" / fileName;
    assetPath = std::filesystem::weakly_canonical(assetPath);

    if (!texture.loadFromFile(assetPath.string())) {
        std::cerr << "Failed to load texture for Timer: " << assetPath << std::endl;
    }
}

int Timer::digitToFrame(int digit) {
    if (digit >= 0 && digit <= 9) {
        return digit;
    }
    return 0;
}

void Timer::update(float deltaTime, sf::Vector2f playerPosition) {
    elapsedSeconds += deltaTime;

    int totalSeconds = static_cast<int>(elapsedSeconds);
    if (totalSeconds > maxMinutes * 60) {
        totalSeconds = maxMinutes * 60;
    }

    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    sprites[0]->setTextureRect(sf::IntRect({ digitToFrame(minutes / 10) * frameWidth, 0 }, { frameWidth, frameHeight }));
    sprites[1]->setTextureRect(sf::IntRect({ digitToFrame(minutes % 10) * frameWidth, 0 }, { frameWidth, frameHeight }));
    sprites[2]->setTextureRect(sf::IntRect({ 10 * frameWidth, 0 }, { frameWidth, frameHeight }));  // colon
    sprites[3]->setTextureRect(sf::IntRect({ digitToFrame(seconds / 10) * frameWidth, 0 }, { frameWidth, frameHeight }));
    sprites[4]->setTextureRect(sf::IntRect({ digitToFrame(seconds % 10) * frameWidth, 0 }, { frameWidth, frameHeight }));

    float spacing = frameWidth * 2.f * 1.1f;

    float posX = playerPosition.x - spacing * 2.f;

    float posY = playerPosition.y - 500.f;

    for (int i = 0; i < 5; ++i) {
        sprites[i]->setPosition({ posX + spacing * i, posY });
    }
}


void Timer::draw(sf::RenderWindow& window) {
    for (auto& spriteOpt : sprites) {
        if (spriteOpt) {
            window.draw(*spriteOpt);
        }
    }
}
