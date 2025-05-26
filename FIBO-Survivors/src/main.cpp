#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Angle.hpp>
#include <filesystem>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>

#include "Skill.h"
#include "Bullet.h"
#include "Monster.h"
#include "helper.h"

// --- Rects Intersect helper for SFML 3.x ---
bool rectsIntersect(const sf::FloatRect& a, const sf::FloatRect& b) {
    return (a.position.x < b.position.x + b.size.x) && (a.position.x + a.size.x > b.position.x) &&
        (a.position.y < b.position.y + b.size.y) && (a.position.y + a.size.y > b.position.y);
}

int main(int argc, char* argv[])
{
    // File Path Settings
    std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
    std::filesystem::path exeDir = exePath.parent_path();
    std::string fileName = "FIBOGoose.png";
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "entity" / "player" / fileName;
    assetPath = std::filesystem::weakly_canonical(assetPath);

    // Load bullet texture
    // (Blue)
    std::string B_bulletFile = "Bullet_Bluefire_blue.png";
    std::filesystem::path B_bulletPath = exeDir / ".." / ".." / "assets" / "entity" / "bullet" / B_bulletFile;
    B_bulletPath = std::filesystem::weakly_canonical(B_bulletPath);

    // (Amethyst)
    std::string Ar_bulletFile = "Bullet_Bluefire_amethyst.png";
    std::filesystem::path Ar_bulletPath = exeDir / ".." / ".." / "assets" / "entity" / "bullet" / Ar_bulletFile;
    Ar_bulletPath = std::filesystem::weakly_canonical(Ar_bulletPath);

    // (Red)
    std::string R_bulletFile = "Bullet_Bluefire_red.png";
    std::filesystem::path R_bulletbulletPath = exeDir / ".." / ".." / "assets" / "entity" / "bullet" / R_bulletFile;
    R_bulletbulletPath = std::filesystem::weakly_canonical(R_bulletbulletPath);

    // Load monster texture
    std::string capaFile = "Sprite-Capa-stand.png";
    std::filesystem::path capaPath = exeDir / ".." / ".." / "assets" / "entity" / "monster" / capaFile;
    capaPath = std::filesystem::weakly_canonical(capaPath);

    // Window and player setup
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "FIBO Survivors");

    // --- Load sound effect buffer (quack) ---
    std::string quackFile = "pain_Quack.wav";
    std::filesystem::path quackPath = exeDir / ".." / ".." / "assets" / "entity" / "sound" / quackFile;
    quackPath = std::filesystem::weakly_canonical(quackPath);
    sf::SoundBuffer quackBuffer;
    if (!quackBuffer.loadFromFile(quackPath.string())) {
        std::cerr << "Failed to load quack sound: " << quackPath << std::endl;
    }
    sf::Sound quackSound{ quackBuffer };
    quackSound.setVolume(100.f); // ปรับความดัง SFX

    // --- Load sound effect buffer (fire) ---
    std::string fireSfxFile = "fire_torch_whoosh.wav";
    std::filesystem::path fireSfxPath = exeDir / ".." / ".." / "assets" / "entity" / "sound" / fireSfxFile;
    fireSfxPath = std::filesystem::weakly_canonical(fireSfxPath);
    sf::SoundBuffer fireSfxBuffer;
    if (!fireSfxBuffer.loadFromFile(fireSfxPath.string())) {
        std::cerr << "Failed to load fire SFX: " << fireSfxPath << std::endl;
    }
    sf::Sound fireSfx{ fireSfxBuffer };
    fireSfx.setVolume(40.f); // ปรับความดังตามต้องการ

    // --- Load sound effect buffer (skill) ---
    std::string skillSfxFile = "skill_sfx.wav";
    std::filesystem::path skillSfxPath = exeDir / ".." / ".." / "assets" / "entity" / "sound" / skillSfxFile;
    skillSfxPath = std::filesystem::weakly_canonical(skillSfxPath);
    sf::SoundBuffer skillSfxBuffer;
    if (!skillSfxBuffer.loadFromFile(skillSfxPath.string())) {
        std::cerr << "Failed to load skill SFX: " << skillSfxPath << std::endl;
    }
    sf::Sound skillSfx{ skillSfxBuffer };
    skillSfx.setVolume(70.f); // ปรับความดังตามต้องการ

    // --- Load and play BGM ---
    std::string bgmFile = "Path_Goblin_King.wav";
    std::filesystem::path bgmPath = exeDir / ".." / ".." / "assets" / "entity" / "sound" / bgmFile;
    bgmPath = std::filesystem::weakly_canonical(bgmPath);

    sf::Music bgm;
    if (!bgm.openFromFile(bgmPath.string())) {
        std::cerr << "Failed to load BGM: " << bgmPath << std::endl;
        return -1;
    }
    bgm.setVolume(100.f);
    bgm.setLooping(true); // ให้เพลงวน
    bgm.play();

    // --- Custom Cursor Setup ---
    std::string cursorFiles[3] = { "cursor_blue.png", "cursor_amethyst.png", "cursor_red.png" };
    sf::Texture cursorTextures[3];
    for (int i = 0; i < 3; ++i) {
        std::filesystem::path cursorPath = exeDir / ".." / ".." / "assets" / "entity" / "cursor" / cursorFiles[i];
        cursorPath = std::filesystem::weakly_canonical(cursorPath);
        if (!cursorTextures[i].loadFromFile(cursorPath.string())) {
            std::cerr << "Failed to load cursor texture: " << cursorPath << std::endl;
            return -1;
        }
    }
    sf::Sprite cursorSprite{ cursorTextures[0] };
    cursorSprite.setOrigin({ static_cast<float>(cursorTextures[0].getSize().x) / 2.f, static_cast<float>(cursorTextures[0].getSize().y) / 2.f });
    cursorSprite.setScale({ 2.f, 2.f });

    window.setMouseCursorVisible(false);

    sf::Texture playerTexture;
    sf::Sprite playerSprite(playerTexture);

    if (playerTexture.loadFromFile(assetPath.string())) {
        playerSprite.setTexture(playerTexture);
        playerSprite.setTextureRect(sf::IntRect({ 0,0 }, { 32,32 }));
        playerSprite.setOrigin({ 16.f, 16.f });
        playerSprite.setScale({ 5.f, 5.f });
    }
    else {
        std::cerr << "Failed to load player texture: " << assetPath << std::endl;
        return -1;
    }

    // Map tile settings
    std::string mapFile = "GrassTile.png";
    std::filesystem::path mapPath = exeDir / ".." / ".." / "assets" / "map" / mapFile;
    mapPath = std::filesystem::weakly_canonical(mapPath);

    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile(mapPath.string())) {
        std::cerr << "Failed to load map tile: " << mapPath << std::endl;
        return -1;
    }
    sf::Sprite tile(tileTexture);

    // --- Bullet system setup ---
    sf::Texture bulletTextureBlue, bulletTextureAmethyst, bulletTextureRed;
    if (!bulletTextureBlue.loadFromFile(B_bulletPath.string())) {
        std::cerr << "Failed to load bullet texture: " << B_bulletPath << std::endl;
        return -1;
    }
    if (!bulletTextureAmethyst.loadFromFile(Ar_bulletPath.string())) {
        std::cerr << "Failed to load bullet texture: " << Ar_bulletPath << std::endl;
        return -1;
    }
    if (!bulletTextureRed.loadFromFile(R_bulletbulletPath.string())) {
        std::cerr << "Failed to load bullet texture: " << R_bulletbulletPath << std::endl;
        return -1;
    }
    std::vector<Bullet> bullets;

    // Bullet type: 1=Blue, 2=Amethyst, 3=Red
    int bulletType = 1;
    bool spacePressedLastFrame = false;

    float baseFireRate = 1.0f;
    float fireRateModifier = 0.0f;
    float baseDamage = 10.0f;
    float damageModifier = 0.0f;
    float bulletSpeed = 200.0f;

    sf::Clock fireClock;
    sf::Clock playerAnimClock;

    float frameDuration = 0.1f;
    int currentFrame = 0;
    const int numFrames = 4;
    bool facingRight = true;

    // --- Monster system setup ---
    sf::Texture capaTexture;
    if (!capaTexture.loadFromFile(capaPath.string())) {
        std::cerr << "Failed to load monster texture: " << capaPath << std::endl;
        return -1;
    }
    std::vector<Monster> monsters;
    sf::Clock monsterSpawnClock;
    const float monsterSpawnInterval = 0.5f;
    const int maxMonsters = 10;

    // --- Skill system setup ---
    Skill skill(6.0f, 6);
    skill.update(1.1f); // ทำให้เริ่มที่เฟรม 2 (คูลดาวน์ทันที)
    sf::Clock skillClock;
    bool skillBulletsSpawned = false; // เพิ่ม flag

    // --- Skill UI SpriteSheet ---
    sf::Texture skillUiTexture;
    std::filesystem::path skillUiPath = exeDir / ".." / ".." / "assets" / "entity" / "skill" / "Bullet_Bluefire_Amethyst_CD.png";
    skillUiPath = std::filesystem::weakly_canonical(skillUiPath);
    if (!skillUiTexture.loadFromFile(skillUiPath.string())) {
        std::cerr << "Failed to load skill UI texture: " << skillUiPath << std::endl;
        return -1;
    }
    const int skillUiFrameCount = 6;
    const int skillUiFrameWidth = skillUiTexture.getSize().x;
    const int skillUiFrameHeight = skillUiTexture.getSize().y / skillUiFrameCount;

    // Player position
    sf::Vector2f playerPosition = window.getView().getCenter();

    // Highlight timer for player
    float playerHighlightTimer = 0.f;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);

        // --- Skill update ---
        float dtSkill = skillClock.restart().asSeconds();
        skill.update(dtSkill);

        // --- Skill: Shoot purple bullets around player every 6 seconds ---
        // ยิงแค่ครั้งเดียวต่อรอบ (เฉพาะ frame 1)
        if (skill.isReady() && !skillBulletsSpawned) {
            const int bulletCount = 8;
            float angleStep = 2 * 3.14159265f / bulletCount;
            float radius = 60.f;
            for (int i = 0; i < bulletCount; ++i) {
                float angle = i * angleStep;
                sf::Vector2f dir(std::cos(angle), std::sin(angle));
                sf::Vector2f bulletStart = playerPosition + dir * radius;
                sf::Vector2f bulletTarget = playerPosition + dir * (radius + 10.f);
                bullets.emplace_back(
                    bulletTextureAmethyst,
                    bulletStart,
                    bulletTarget,
                    bulletSpeed,
                    baseDamage,
                    damageModifier,
                    true // isSkillBullet
                );
            }
            skillSfx.play();
            skillBulletsSpawned = true;
        }
        if (skill.getFrame() != 1) {
            skillBulletsSpawned = false;
        }

        // Handle bullet type switching with Spacebar
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (!spacePressedLastFrame) {
                bulletType = bulletType % 3 + 1; // 1->2->3->1
                spacePressedLastFrame = true;
            }
        }
        else {
            spacePressedLastFrame = false;
        }

        // Movement input
        const float speed = 1.f;
        sf::Vector2f movement{ 0.f, 0.f };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            movement.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            movement.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            movement.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            movement.x += 1.f;

        // Normalize movement
        if (movement.x != 0.f || movement.y != 0.f)
        {
            float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
            movement.x = (movement.x / length) * speed;
            movement.y = (movement.y / length) * speed;
        }

        playerPosition += movement;
        playerSprite.setPosition(playerPosition);

        // Animation update (player)
        if (playerAnimClock.getElapsedTime().asSeconds() > frameDuration)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            playerSprite.setTextureRect(sf::IntRect({ currentFrame * 32, 0 }, { 32, 32 }));
            playerAnimClock.restart();
        }

        // Flip sprite based on direction
        if (movement.x < 0) {
            if (facingRight) {
                facingRight = false;
                playerSprite.setScale({ -5.f, 5.f });
                playerSprite.setOrigin({ 16.f, 16.f });
            }
        }
        else if (movement.x > 0) {
            if (!facingRight) {
                facingRight = true;
                playerSprite.setScale({ 5.f, 5.f });
                playerSprite.setOrigin({ 16.f, 16.f });
            }
        }

        // Map Generation
        const int tileSize = tileTexture.getSize().x;
        const int N = 20;

        int px = static_cast<int>(std::floor(playerPosition.x / tileSize));
        int py = static_cast<int>(std::floor(playerPosition.y / tileSize));
        for (int y = -N; y <= N; ++y) {
            for (int x = -N; x <= N; ++x) {
                tile.setPosition({
                     static_cast<float>((px + x) * tileSize),
                     static_cast<float>((py + y) * tileSize)
                    });

                window.draw(tile);
            }
        }

        // --- Monster spawn ---
        if (monsterSpawnClock.getElapsedTime().asSeconds() > monsterSpawnInterval && monsters.size() < maxMonsters) {
            sf::Vector2f spawnPos = randomMonsterSpawn(window.getView());
            if (std::hypot(spawnPos.x - playerPosition.x, spawnPos.y - playerPosition.y) > 300.f) {
                monsters.emplace_back(capaTexture, spawnPos);
                monsterSpawnClock.restart();
            }
        }

        // --- Update & draw monsters ---
        static sf::Clock monsterAnimClock;
        float dt = monsterAnimClock.restart().asSeconds();
        bool playerHit = false;
        for (auto it = monsters.begin(); it != monsters.end(); ) {
            it->update(dt, playerPosition);
            // Player collision
            sf::FloatRect playerHitbox = playerSprite.getGlobalBounds();
            float shrink = 0.5f;
            playerHitbox.position.x += playerHitbox.size.x * shrink / 2.f;
            playerHitbox.position.y += playerHitbox.size.y * shrink / 2.f;
            playerHitbox.size.x *= (1.f - shrink);
            playerHitbox.size.y *= (1.f - shrink);

            if (it->checkPlayerCollision(playerHitbox)) {
                if (!it->isDead()) {
                    it->onHitPlayer();
                    playerHit = true;
                }
            }
            ++it;
        }

        // --- Bullet vs Monster collision ---
        for (auto mIt = monsters.begin(); mIt != monsters.end(); ++mIt) {
            if (mIt->isDead()) continue;
            for (auto bIt = bullets.begin(); bIt != bullets.end(); ) {
                if (mIt->checkBulletCollision(bIt->getHitbox())) {
                    mIt->onHitByBullet();
                    // ถ้าไม่ใช่ skill bullet ให้ลบ
                    if (!bIt->isSkill()) {
                        bIt = bullets.erase(bIt);
                    }
                    else {
                        ++bIt;
                    }
                }
                else {
                    ++bIt;
                }
            }
        }

        // --- Remove dead monsters ---
        monsters.erase(
            std::remove_if(monsters.begin(), monsters.end(), [](const Monster& m) { return m.isDead(); }),
            monsters.end()
        );

        // --- Fire bullets toward mouse cursor ---
        float fireInterval = 1.0f / (baseFireRate + fireRateModifier);
        if (fireClock.getElapsedTime().asSeconds() >= fireInterval) {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePixel);

            // ขยับจุดกำเนิดกระสุนออกจาก player
            sf::Vector2f dir = mouseWorld - playerPosition;
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len != 0) dir /= len;
            sf::Vector2f bulletStart = playerPosition + dir * 40.f;

            // เลือก texture ตาม bulletType
            const sf::Texture* currentBulletTexture = nullptr;
            if (bulletType == 1) currentBulletTexture = &bulletTextureBlue;
            else if (bulletType == 2) currentBulletTexture = &bulletTextureAmethyst;
            else if (bulletType == 3) currentBulletTexture = &bulletTextureRed;

            bullets.emplace_back(
                *currentBulletTexture,
                bulletStart,
                mouseWorld,
                bulletSpeed,
                baseDamage,
                damageModifier,
                false // ไม่ใช่ skill bullet
            );
            fireSfx.play();
            fireClock.restart();
        }

        // --- Update and draw bullets ---
        static sf::Clock bulletAnimClock;
        float dtBullet = bulletAnimClock.restart().asSeconds();
        for (auto it = bullets.begin(); it != bullets.end(); ) {
            it->update(dtBullet);
            if (!it->isAlive())
                it = bullets.erase(it);
            else
                ++it;
        }
        for (const auto& b : bullets)
            b.draw(window);

        // --- Draw monsters ---
        for (const auto& m : monsters)
            m.draw(window);

        // --- Player highlight on hit ---
        static bool playerWasHitLastFrame = false;
        if (playerHit && !playerWasHitLastFrame) {
            quackSound.play(); // เล่นเสียงเมื่อโดน
            playerHighlightTimer = 0.2f;
        }
        playerWasHitLastFrame = playerHit;

        if (playerHighlightTimer > 0.f) {
            playerSprite.setColor(sf::Color(255, 80, 80));
            playerHighlightTimer -= dt;
        }
        else {
            playerSprite.setColor(sf::Color::White);
        }

        // Center the view on the player
        sf::View view = window.getView();
        view.setCenter(playerPosition);
        window.setView(view);
        window.draw(playerSprite);

        // --- Draw skill cooldown UI (top-left, not at edge) ---
        {
            float margin = 40.f;
            float size = 40.f;
            float uiX = view.getCenter().x - view.getSize().x / 2.f + margin;
            float uiY = view.getCenter().y - view.getSize().y / 2.f + margin;

            // ตรวจสอบขนาด texture
            if (skillUiTexture.getSize().x < 16 || skillUiTexture.getSize().y < 16 * skill.getFrameCount()) {
                std::cerr << "Skill UI texture size is too small! ("
                    << skillUiTexture.getSize().x << "x" << skillUiTexture.getSize().y << ")" << std::endl;
            }
            else {
                int yOffset = (skill.getFrame() - 1) * 16;
                sf::Sprite skillUiSprite(skillUiTexture);
                skillUiSprite.setTextureRect(sf::IntRect({ 0, yOffset }, { 16, 16 }));
                skillUiSprite.setPosition({ uiX, uiY });
                skillUiSprite.setScale({ 4.f, 4.f });

                // สามารถปรับสีหรือเอฟเฟกต์ได้ตามต้องการ
                skillUiSprite.setColor(sf::Color(255, 255, 255, 255));
                window.draw(skillUiSprite);
            }
        }

        // --- Draw custom cursor ---
        int cursorIndex = bulletType - 1;
        cursorSprite.setTexture(cursorTextures[cursorIndex], true);
        cursorSprite.setOrigin({ static_cast<float>(cursorTextures[cursorIndex].getSize().x) / 2.f, static_cast<float>(cursorTextures[cursorIndex].getSize().y) / 2.f });

        sf::Vector2i mousePixel{ sf::Mouse::getPosition(window) };
        sf::Vector2f mouseWorld{ window.mapPixelToCoords(mousePixel) };
        cursorSprite.setPosition(mouseWorld);
        window.draw(cursorSprite);

        window.display();
    }
}
