#version 420 core
// BUILT IN INPUTS
// in int gl_VertexID;
// in int gl_InstanceID;

// buffer data
layout(location = 0) in vec2 vert;
layout(location = 1) in vec3 charIdxLineIdxChar;

uniform vec2 res;
uniform vec3 anchorSize;

// outputs to fragment shader
out vec2 UV;

void main(){ 
    gl_Position = vec4(
        anchorSize.x + vert.x + charIdxLineIdxChar.x * (1 / 16.0f),
        anchorSize.y + vert.y - charIdxLineIdxChar.y * (1 / 8.0f),
        0,
        1);
    UV = vec2(
        mod(charIdxLineIdxChar.z, 16.0f) * 0.0625f + vert.x,
        floor(charIdxLineIdxChar.z / 16.0f) * 0.125f - vert.y);
}