#ifndef ASTEROIDSGAME_H
#define ASTEROIDSGAME_H

#include "ParticleSystem/ParticleSystem.h"
#include "Rectangle/GameObject/Bullet/Bullet.h"
#include "Rectangle/GameObject/PolyShape/Asteroid/Asteroid.h"
#include "Rectangle/GameObject/PolyShape/Ship/Ship.h"
#include "Shader/Shader.h"
#include "IO/IO.h"
#include "Audio/Audio.h"
#include <vector>

namespace Asteroids {
    class AsteroidsGame {
    private:
        Asteroids::Audio shootSound;
        Asteroids::Audio explosionSound;
        float width;
        float height;
        int score = 0;
        std::vector<Bullet> bullets = {};
        std::vector<Asteroid> asteroids = {};
        std::vector<Particle> particles = {};
        int lives = 3;
        Ship ship;
        Shader shader = Shader("./default");
        ParticleSystem particleSystem = ParticleSystem();;

    public:
        AsteroidsGame(int noAsteroids, float width, float height);
        void Update(InputState& inputState);
        void DrawFrame();
        void HandleEvents(InputState& inputState);
        int GetScore();
    };
}

#endif