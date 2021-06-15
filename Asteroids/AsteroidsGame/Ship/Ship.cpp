#include "Ship.h"
#include <glm/glm.hpp>
#include <cmath>

namespace Asteroids {
    Ship::Ship(float x, float y, float angle, float dx, float dy, float dAngle, Engine::ParticleSystem* particleSystem)
        : particleSystem(particleSystem), Engine::PolyShape(x, y, angle, dx, dy, dAngle, 10, std::vector<std::pair<float, float>>()) {
        points.push_back(std::pair<float, float>(0.0f, -1.0f));
        points.push_back(std::pair<float, float>(1.0f, 1.0f));
        points.push_back(std::pair<float, float>(0.0f, 0.0f));
        points.push_back(std::pair<float, float>(-1.0f, 1.0f));
    }

    void Ship::Shield(int duration) {
        shield = duration;
        fullShield = duration;
    }

    int Ship::Shield() {
        return shield;
    }

    int Ship::FullShield() {
        return fullShield;
    }

    void Ship::Explode() {
        alive = false;
    }

    void Ship::Upgrade() {
        upgradeLevel++;
        upgradeLevel = upgradeLevel > 2 ? 2 : upgradeLevel;
    }

    int Ship::CurrentLevel() {
        return upgradeLevel;
    }

    void Ship::Accelerate(float power) {
        dx += power * std::sin(angle);
        dy -= power * std::cos(angle);
        particleSystem->Thrust(x, y, dx, dy, angle);
    }

    void Ship::Update(float maxX, float maxY, bool wrap) {
        if (shield) { shield--; }
        PolyShape::Update(maxX, maxY, wrap);
    }

    std::vector<Bullet> Ship::Fire(float power) {
        std::vector<Bullet> bullets = {};
        bullets.push_back(Bullet(x, y, dx + power * std::sin(angle), dy + power * -std::cos(angle)));
        if (upgradeLevel > 0) {
            bullets.push_back(Bullet(x, y, dx + power * std::sin(angle - 0.2f), dy + power * -std::cos(angle - 0.2f)));
            bullets.push_back(Bullet(x, y, dx + power * std::sin(angle + 0.2f), dy + power * -std::cos(angle + 0.2f)));
        }
        if (upgradeLevel > 1) {
            bullets.push_back(Bullet(x, y, dx + power * std::sin(angle - 0.1f), dy + power * -std::cos(angle - 0.1f)));
            bullets.push_back(Bullet(x, y, dx + power * std::sin(angle + 0.1f), dy + power * -std::cos(angle + 0.1f)));
        }
        return bullets;
    }
}