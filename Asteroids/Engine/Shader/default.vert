#version 420 core
// BUILT IN INPUTS
// in int gl_VertexID;
// in int gl_InstanceID;

// buffer data
layout(location = 0) in vec2 vertexPosition_modelspace;

// uniform inputs
uniform vec3 col;

// outputs to fragment shader
out vec3 fragmentColor;

void main(){ 
    gl_Position = vec4(vertexPosition_modelspace,0,1);
    fragmentColor = col;
}