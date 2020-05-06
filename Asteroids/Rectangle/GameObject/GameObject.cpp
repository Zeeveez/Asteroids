#include "GameObject.h"

namespace Asteroids {
    GameObject::GameObject(float x, float y, float dx, float dy, bool alive)
        : x(x), y(y), dx(dx), dy(dy), alive(alive) {}

    bool GameObject::IsAlive() {
        return alive;
    }

    void GameObject::Kill() {
        alive = false;
    }
}