#ifndef ASTEROIDSGAME_H
#define ASTEROIDSGAME_H

#include "Engine/ParticleSystem/ParticleSystem.h"
#include "Bullet/Bullet.h"
#include "Asteroid/Asteroid.h"
#include "Ship/Ship.h"
#include "Engine/Shader/Shader.h"
#include "Engine/IO/IO.h"
#include "Engine/Audio/Audio.h"
#include <vector>

namespace Asteroids {
    class AsteroidsGame {
    private:
        Engine::Audio shootSound;
        Engine::Audio explosionSound;
        float width;
        float height;
        int score = 0;
        std::vector<Bullet> bullets = {};
        std::vector<Asteroid> asteroids = {};
        std::vector<Engine::Particle> particles = {};
        int lives = 3;
        Ship ship;
        Engine::Shader shader = Engine::Shader("./default");
        Engine::ParticleSystem particleSystem = Engine::ParticleSystem();;

    public:
        AsteroidsGame(int noAsteroids, float width, float height);
        void Update(Engine::InputState& inputState);
        void DrawFrame();
        void HandleEvents(Engine::InputState& inputState);
        int GetScore();
    };
}

#endif