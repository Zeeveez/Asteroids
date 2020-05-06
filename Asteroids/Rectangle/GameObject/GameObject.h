#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../../Shader/Shader.h"
#include "../Rectangle.h"

namespace Asteroids {
    class GameObject {
    protected:
        float x;
        float y;
        float dx;
        float dy;
        bool alive;

        GameObject() = default;
        virtual ~GameObject() = default;
        GameObject(float x, float y, float dx, float dy, bool alive);

    public:
        virtual void Draw(Shader& shader, float width, float height) = 0;
        virtual void Update(float maxX, float maxY, bool wrap = false) = 0;
        virtual Rectangle GetBounds() = 0;
        bool IsAlive();
        void Kill();
    };
}
#endif