#version 330 core
// BUILT IN INPUTS
// in vec4 gl_FragCoord;
// in bool gl_FrontFacing;
// in vec2 gl_PointCoord;

// inputs
in vec3 fragmentColor;

// outputs
out vec3 color;

void main(){
	color = fragmentColor;
}