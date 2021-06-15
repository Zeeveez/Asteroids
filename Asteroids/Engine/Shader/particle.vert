#version 330 core
// BUILT IN INPUTS
// in int gl_VertexID;
// in int gl_InstanceID;

// buffer data
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 particleColor;

// outputs to fragment shader
out vec3 fragmentColor;

void main() {
    gl_Position = vec4(vertexPosition_modelspace.xy,0,1);
    gl_PointSize = vertexPosition_modelspace.z;
    fragmentColor = particleColor;
}