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

// Input: It uses texture coords as the random number seed.
// Output: Random number: [0,1), that is between 0.0 and 0.999999... inclusive.
// Author: Michael Pohoreski
// Copyright: Copyleft 2012 :-)
// NOTE: This has been upgraded to version 3 !!
float random( vec2 p )
{
  // We need irrationals for pseudo randomness.
  // Most (all?) known transcendental numbers will (generally) work.
  const vec2 r = vec2(
    23.1406926327792690,  // e^pi (Gelfond's constant)
     2.6651441426902251); // 2^sqrt(2) (Gelfond–Schneider constant)
  return fract( cos( mod( 123456789., 1e-7 + 256. * dot(p,r) ) ) );  
}


//void main(){
//    color = texture(screenTexture,
//        vec2(
//            mod(fragUV.x, 0.5f)*2.0f,
//            mod(fragUV.y, 0.5f)*2.0f
//        )
//    );
//    color = vec4(texture(screenTexture,fragUV).xyz * random(fragUV), 1.0f);
//}

const float offset = 1.0 / 1000.0;  

void main()
{
    vec2 offsets[25] = vec2[](
        vec2(-offset*2.0f,  offset*2.0f), // top-left
        vec2(-offset,       offset*2.0f),
        vec2(0.0f,          offset*2.0f),
        vec2(offset,        offset*2.0f),
        vec2(offset*2.0f,   offset*2.0f), // top-right
        vec2(-offset*2.0f,  offset), 
        vec2(-offset,       offset), 
        vec2(0.0f,          offset), 
        vec2(offset,        offset), 
        vec2(offset*2.0f,   offset), 
        vec2(-offset*2.0f,  0.0f), 
        vec2(-offset,       0.0f), 
        vec2(0.0f,          0.0f), 
        vec2(offset,        0.0f), 
        vec2(offset*2.0f,   0.0f), 
        vec2(-offset*2.0f,  -offset), 
        vec2(-offset,       -offset), 
        vec2(0.0f,          -offset), 
        vec2(offset,        -offset), 
        vec2(offset*2.0f,   -offset), 
        vec2(-offset*2.0f,  -offset*2.0f), 
        vec2(-offset,       -offset*2.0f),
        vec2(0.0f,          -offset*2.0f),
        vec2(offset,        -offset*2.0f),
        vec2(offset*2.0f,   -offset*2.0f)
    );


    float kernel[25] = float[](
        1.0 / 32, 2.0 / 32, 4.0 / 32, 2.0 / 32, 1.0 / 32,
        2.0 / 32, 4.0 / 32, 8.0 / 32, 4.0 / 32, 2.0 / 32,
        4.0 / 32, 8.0 / 32, 32.0 / 32, 8.0 / 32, 4.0 / 32,
        2.0 / 32, 4.0 / 32, 8.0 / 32, 4.0 / 32, 2.0 / 32,
        1.0 / 32, 2.0 / 32, 4.0 / 32, 2.0 / 32, 1.0 / 32
    );
   
    vec3 sampleTex[25];
    for(int i = 0; i < 25; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, fragUV.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 25; i++)
        col += sampleTex[i] * kernel[i];
    
    color = vec4(col, 1.0);
} 











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



//const float offset = 1.0 / 500.0;  
//
//void main()
//{
//    vec2 offsets[9] = vec2[](
//        vec2(-offset,  offset), // top-left
//        vec2( 0.0f,    offset), // top-center
//        vec2( offset,  offset), // top-right
//        vec2(-offset,  0.0f),   // center-left
//        vec2( 0.0f,    0.0f),   // center-center
//        vec2( offset,  0.0f),   // center-right
//        vec2(-offset, -offset), // bottom-left
//        vec2( 0.0f,   -offset), // bottom-center
//        vec2( offset, -offset)  // bottom-right    
//    );
//
//
//    float kernel[9] = float[](
//        1.0 / 16, 2.0 / 16, 1.0 / 16,
//        2.0 / 16, 4.0 / 16, 2.0 / 16,
//        1.0 / 16, 2.0 / 16, 1.0 / 16  
//    );
//   
//    vec3 sampleTex[9];
//    for(int i = 0; i < 9; i++)
//    {
//        sampleTex[i] = vec3(texture(screenTexture, fragUV.st + offsets[i]));
//    }
//    vec3 col = vec3(0.0);
//    for(int i = 0; i < 9; i++)
//        col += sampleTex[i] * kernel[i];
//    
//    color = vec4(col, 1.0);
//} 