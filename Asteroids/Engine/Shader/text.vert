#version 330 core
// BUILT IN INPUTS
// in int gl_VertexID;
// in int gl_InstanceID;

// buffer data
layout(location = 0) in vec2 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// outputs to fragment shader
out vec2 UV;

void main(){ 
    gl_Position = vec4(vertexPosition_modelspace,0,1);
    UV = vec2(vertexUV.x, 1-vertexUV.y);
}