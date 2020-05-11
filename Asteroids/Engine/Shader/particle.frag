#version 330 core
// BUILT IN INPUTS
// in vec4 gl_FragCoord;
// in bool gl_FrontFacing;
// in vec2 gl_PointCoord;

// uniform inputs
uniform float size;
uniform vec2 pos;
uniform vec3 col;

// outputs
out vec3 color;

void main(){
	vec2 normalisedPos = gl_FragCoord.xy - pos;
	float dist = distance(vec2(0,0), normalisedPos);
	if(dist > size / 2) { discard; }
	color = col;
}