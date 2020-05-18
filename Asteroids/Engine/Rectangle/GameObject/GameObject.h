#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Engine/Shader/Shader.h"
#include "Engine/Rectangle/Rectangle.h"

namespace Engine {
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
        virtual void Draw(Shader& shader, float width, float height, float r, float g, float b) = 0;
        virtual void Update(float maxX, float maxY, bool wrap = false) = 0;
        virtual Rectangle GetBounds() = 0;
        bool IsAlive();
        void Kill();
    };
}
#endif