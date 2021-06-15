#version 460 core
// BUILT IN INPUTS
// in vec4 gl_FragCoord;
// in bool gl_FrontFacing;
// in vec2 gl_PointCoord;

// inputs from vertex shader
in vec2 UV;

// uniforms
uniform sampler2D textureID;

// outputs
out vec4 color;

void main(){
    color = texture(textureID, UV);
    if(color.a <= 0){
        discard;
    }
}