#ifndef BULLET_H
#define BULLET_H

#include "../GameObject.h"

namespace Asteroids {
    class Bullet : public GameObject {
    public:
        Bullet(float x, float y, float dx, float dy);
        void Update(float maxX, float maxY, bool wrap = false) override;
        void Draw(Shader& shader, float width, float height) override;
        Rectangle GetBounds() override;
    };
}

#endif