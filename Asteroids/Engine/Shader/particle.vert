#version 460 core
// BUILT IN INPUTS
// in int gl_VertexID;
// in int gl_InstanceID;

// buffer data
layout(location = 0) in vec2 vert;
layout(location = 1) in vec3 particlePosSize;
layout(location = 2) in vec3 particleColor;

uniform vec2 res;

// outputs to fragment shader
out vec3 fragmentColor;

void main() {
    gl_Position = vec4(
        particlePosSize.z * vert.x / res.x + particlePosSize.x,
        particlePosSize.z * vert.y / res.y + particlePosSize.y,
        0,
        1);
    fragmentColor = particleColor;
}