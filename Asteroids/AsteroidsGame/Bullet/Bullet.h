#ifndef BULLET_H
#define BULLET_H

#include "Engine/Rectangle/GameObject/GameObject.h"

namespace Asteroids {
    class Bullet : public Engine::GameObject {
    public:
        Bullet(float x, float y, float dx, float dy);
        void Update(float maxX, float maxY, bool wrap = false) override;
        void Draw(Engine::Shader& shader, float width, float height, float r = 1.0f, float g = 1.0f, float b = 1.0f) override;
        Engine::Rectangle GetBounds() override;
    };
}

#endif