#ifndef SHIP_H
#define SHIP_H

#include "Rectangle/GameObject/PolyShape/PolyShape.h"
#include "Rectangle/GameObject/Bullet/Bullet.h"
#include "ParticleSystem/ParticleSystem.h"

namespace Asteroids {
    class Ship : public PolyShape {
    private:
        ParticleSystem* particleSystem;
        int fullShield = 0;
        int shield = 0;
    public:
        Ship() = default;
        Ship(float x, float y, float angle, float dx, float dy, float dAngle, ParticleSystem* particleSystem);
        void Shield(int duration);
        int Ship::Shield();
        void Explode();
        void Accelerate(float power);
        void Update(float maxX, float maxY, bool wrap = true);
        void Draw(Shader& shader, float width, float height);
        Bullet Fire(float power);
    };
}

#endif