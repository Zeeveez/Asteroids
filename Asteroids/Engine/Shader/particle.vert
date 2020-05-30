#version 330 core
// BUILT IN INPUTS
// in int gl_VertexID;
// in int gl_InstanceID;

// buffer data
layout(location = 0) in vec2 vertexPosition_modelspace;

// uniform inputs
uniform float size;
uniform vec3 col;

void main() {
    gl_Position = vec4(vertexPosition_modelspace,0,1);
    gl_PointSize = size;
}