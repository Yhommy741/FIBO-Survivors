#pragma once

class Skill {
public:
    Skill(float cooldown, int frameCount);
    void update(float dt);
    bool isReady() const;
    int getFrame() const;
    int getFrameCount() const;
    float getCooldown() const;
    float getTimeLeft() const;
    void reset();
private:
    float cooldown;
    int frameCount;
    float timer;
    int frame;
};
