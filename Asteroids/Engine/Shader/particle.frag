#version 330 core
// BUILT IN INPUTS
// in vec4 gl_FragCoord;
// in bool gl_FrontFacing;
// in vec2 gl_PointCoord;

// uniform inputs
uniform float size;
uniform vec3 col;

// outputs
out vec3 color;

void main(){
	color = col;
}