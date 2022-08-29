#version 420 core
// BUILT IN INPUTS
// in int gl_VertexID;
// in int gl_InstanceID;

// buffer data
layout(location = 0) in vec2 vertPos;
layout(location = 1) in vec2 UV;

out vec2 fragUV;

void main(){ 
    gl_Position = vec4(vertPos,0,1);
    fragUV = UV;
}