#version 460 core
// BUILT IN INPUTS
// in vec4 gl_FragCoord;
// in bool gl_FrontFacing;
// in vec2 gl_PointCoord;

// inputs from vertex shader
in vec2 fragUV;

// outputs
out vec4 color;
  
// uniforms
uniform sampler2D screenTexture;
uniform float time;

const float TWO_PI = 6.2831853072f;
const float PI = 3.1415926535f;

//void main(){
//    color = texture(screenTexture,
//        vec2(
//            mod(fragUV.x, 0.5f)*2.0f,
//            mod(fragUV.y, 0.5f)*2.0f
//        )
//    );
//
//    float fTime = time/100000.0f * TWO_PI - PI;
//    color = texture(screenTexture,
//        vec2(
//            fragUV.x,
//            fragUV.y + sin(fTime*100.0f*fragUV.x)/10.0f
//        )
//    );
//}



const float offset = 1.0 / 300.0;  

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );


    float kernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16  
    );
   
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, fragUV.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    color = vec4(col, 1.0);
} 