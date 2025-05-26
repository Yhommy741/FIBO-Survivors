#include "Skill.h"

Skill::Skill(float cooldown, int frameCount)
    : cooldown(cooldown), frameCount(frameCount), timer(0.f), frame(1) {
}

void Skill::update(float dt) {
    timer += dt;
    if (timer >= 1.0f) {
        timer -= 1.0f;
        frame++;
        if (frame > frameCount) frame = 1;
    }
}
bool Skill::isReady() const { return frame == 1 && timer < 0.1f; }
int Skill::getFrame() const { return frame; }
int Skill::getFrameCount() const { return frameCount; }
float Skill::getCooldown() const { return cooldown; }
float Skill::getTimeLeft() const { return cooldown - ((frame - 1) + timer); }
void Skill::reset() { timer = 0.f; frame = 1; }
