#include "AsteroidsGame.h"
#include "Audio/WAV/WAV.h"
#include <algorithm>

namespace Asteroids {
    AsteroidsGame::AsteroidsGame(int noAsteroids, float width, float height) : width(width), height(height),
        explosionSound(Asteroids::Audio(Asteroids::WAV("./Explosion.wav"))),
        shootSound(Asteroids::Audio(Asteroids::WAV("./Shoot.wav"))) {
        ship = Ship(width / 2, height / 2, 0, 0, 0, 0, &particleSystem);
        ship.Shield(300);
        for (int i = 0; i < noAsteroids; i++) {
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

    void AsteroidsGame::Update(InputState& inputState) {
        for (auto& click : (inputState).clicks) {
            particleSystem.Explosion(click.first, height - click.second);
        }
        (inputState).clicks.clear();

        for (auto& bullet : bullets) {
            bullet.Update(width, height);
        }
        particleSystem.Update(width, height);
        bullets.erase(std::remove_if(
            bullets.begin(), bullets.end(),
            [](Bullet& bullet) {
                return !bullet.IsAlive();
            }), bullets.end());
        for (auto& asteroid : asteroids) {
            asteroid.Update(width, height);
        }

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
        asteroids.clear();
        for (auto& asteroid : newAsteroids) {
            asteroids.push_back(asteroid);
        }

        ship.Update(width, height);
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
        if (ship.IsAlive()) {
            ship.Draw(shader, width, height);
        }
        for (int i = 0; i < lives; i++) {
            Ship lifeShip = Ship((i + 1) * 40.0f, 40.0f, 3.1415926535f, 0.0f, 0.0f, 0.0f, &particleSystem);
            lifeShip.Draw(shader, width, height);
        }
    }

    void AsteroidsGame::HandleEvents(InputState& inputState) {
        if (ship.IsAlive()) {
            if (inputState.keys[GLFW_KEY_W]) { ship.Accelerate(0.15f); }
            if (inputState.keys[GLFW_KEY_A]) { ship.Turn(0.1f); }
            if (inputState.keys[GLFW_KEY_D]) { ship.Turn(-0.1f); }
            if (inputState.keys[GLFW_KEY_SPACE]) {
                inputState.keys[GLFW_KEY_SPACE] = false;
                bullets.push_back(ship.Fire(4));
                shootSound.Play();
            }
        }
    }

    int AsteroidsGame::GetScore() {
        return score;
    }
}