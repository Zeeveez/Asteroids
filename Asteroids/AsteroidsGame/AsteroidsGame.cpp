#include "AsteroidsGame.h"
#include "Engine/Options/Options.h"
#include <algorithm>

namespace Asteroids {
    AsteroidsGame::AsteroidsGame(float width, float height) : width(width), height(height),
        explosionSound(Engine::Audio("./Explosion.wav")),
        shootSound(Engine::Audio("./Shoot.wav")) {
        ship = Ship(width / 2, height / 2, 0, 0, 0, 0, &particleSystem);
        ship.Shield(300);
        for (int i = 0; i < ((stage + 1) * 5); i++) {
            asteroids.push_back(Asteroid(
                fmodf((float)rand(), width),
                fmodf((float)rand(), height),
                ((float)rand()) / RAND_MAX * 360,
                2 * (0.5f - ((float)rand()) / RAND_MAX),
                2 * (0.5f - ((float)rand()) / RAND_MAX),
                0.1f * (0.5f - ((float)rand()) / RAND_MAX),
                50,
                &particleSystem));
        }
    }

    void AsteroidsGame::Update(Engine::InputState& inputState) {
        const float UPGRADE_CHANCE = 0.05f;

        for (auto& bullet : bullets) {
            bullet.Update(width, height);
        }
        bullets.erase(std::remove_if(
            bullets.begin(), bullets.end(),
            [](Bullet& bullet) {
                return !bullet.IsAlive();
            }), bullets.end());
        particleSystem.Update(width, height);
        for (auto& asteroid : asteroids) {
            asteroid.Update(width, height);
        }
        for (auto& upgrade : upgrades) {
            upgrade.Update(width, height, false);
        }
        upgrades.erase(std::remove_if(
            upgrades.begin(), upgrades.end(),
            [](Upgrade& upgrade) {
                return !upgrade.IsAlive();
            }), upgrades.end());

        std::vector<Asteroid> newAsteroids = {};
        for (auto& asteroid : asteroids) {
            bool exploded = false;
            for (auto& bullet : bullets) {
                if (bullet.IsAlive() && bullet.GetBounds().Intersects(asteroid.GetBounds())) {
                    score += 100;
                    exploded = true;
                    explosionSound.Play();
                    bullet.Kill();
                    for (auto& addasteroid : asteroid.Explode()) {
                        newAsteroids.push_back(addasteroid);
                    }
                    if ((float)rand() / RAND_MAX < UPGRADE_CHANCE) {
                        auto pos = asteroid.GetPos();
                        auto vel = asteroid.GetVel();
                        upgrades.push_back(Upgrade(pos.first, pos.second, 0, vel.first * 2, vel.second * 2, 0.075f, 20));
                    }
                }
            }
            if (ship.IsAlive() && ship.GetBounds().Intersects(asteroid.GetBounds())) {
                score += 50;
                for (auto& addasteroid : asteroid.Explode()) {
                    newAsteroids.push_back(addasteroid);
                }
                exploded = true;
                explosionSound.Play();
                if (!ship.Shield()) {
                    ship.Explode();
                    if (lives--) {
                        for (auto& iter : inputState.keys) {
                            iter.second = false;
                        }
                        ship = Ship(width / 2, height / 2, 0, 0, 0, 0, &particleSystem);
                        ship.Shield(300);
                    }
                }
            }
            if (!exploded) {
                newAsteroids.push_back(asteroid);
            }
        }
        for (auto& upgrade : upgrades) {
            if (ship.IsAlive() && ship.GetBounds().Intersects(upgrade.GetBounds())) {
                score += 500;
                ship.Upgrade();
                upgrade.Kill();
            }
        }
        asteroids.clear();
        for (auto& asteroid : newAsteroids) {
            asteroids.push_back(asteroid);
        }

        ship.Update(width, height);

        if (asteroids.size() == 0) {
            stage++;
            for (int i = 0; i < ((stage + 1) * 5); i++) {
                asteroids.push_back(Asteroid(
                    fmodf((float)rand(), width),
                    fmodf((float)rand(), height),
                    ((float)rand()) / RAND_MAX * 360,
                    2 * (0.5f - ((float)rand()) / RAND_MAX),
                    2 * (0.5f - ((float)rand()) / RAND_MAX),
                    0.1f * (0.5f - ((float)rand()) / RAND_MAX),
                    50,
                    &particleSystem));
            }
        }
    }

    void AsteroidsGame::DrawFrame() {
        particleSystem.Render(width, height);
        for (auto& bullet : bullets) {
            if (bullet.IsAlive()) {
                bullet.Draw(shader, width, height);
            }
        }
        for (auto& asteroid : asteroids) {
            if (asteroid.IsAlive()) {
                asteroid.Draw(shader, width, height);
            }
        }
        for (auto& upgrade : upgrades) {
            if (upgrade.IsAlive()) {
                upgrade.Draw(shader, width, height, 1.0f, 1.0f, 0.0f);
            }
        }
        if (ship.IsAlive()) {
            ship.Draw(shader, width, height, 1 - (ship.Shield() ? (float)ship.Shield() / ship.FullShield() : 0), 1.0f, 1.0f);
        }
        for (int i = 0; i < lives; i++) {
            Ship lifeShip = Ship((i + 1) * 40.0f, 40.0f, 3.1415926535f, 0.0f, 0.0f, 0.0f, &particleSystem);
            lifeShip.Draw(shader, width, height);
        }
    }

    void AsteroidsGame::HandleEvents(Engine::InputState& inputState) {
        if (ship.IsAlive()) {
            if (inputState.keys[GLFW_KEY_W]) { ship.Accelerate(0.15f); }
            if (inputState.keys[GLFW_KEY_A]) { ship.Turn(0.1f); }
            if (inputState.keys[GLFW_KEY_D]) { ship.Turn(-0.1f); }
            if (inputState.keys[GLFW_KEY_SPACE]) {
                inputState.keys[GLFW_KEY_SPACE] = false;
                std::vector<Bullet> newBullets = ship.Fire(4);
                bullets.insert(bullets.end(), newBullets.begin(), newBullets.end());
                shootSound.Play();
            }
            if (inputState.keys[GLFW_KEY_B]) {
                inputState.keys[GLFW_KEY_B] = false;
                Engine::Options::drawBounds = !Engine::Options::drawBounds;
            }
        }
    }

    int AsteroidsGame::GetScore() {
        return score;
    }

    int AsteroidsGame::GetStage() {
        return stage;
    }
}