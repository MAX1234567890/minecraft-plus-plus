#version 410 core

in vec2 uv;
in vec3 normal;
in float sunlight;

uniform sampler2D tex;

out vec4 fc;

void main(){
    vec2 _uv=uv;
//    _uv.y=1.0-_uv.y;
    fc=texture(tex,_uv);
    if(fc.w==0.0)discard;


    float fakeLight=1.0;
    //dark sunset
//    if(normal==vec3(-1,0,0))fakeLight=0.8;
//    if(normal==vec3(1,0,0))fakeLight=0.2;
//    if(normal==vec3(0,1,0))fakeLight=0.8;
//    if(normal==vec3(0,-1,0))fakeLight=0.2;
//    if(normal==vec3(0,0,-1))fakeLight=0.6;
//    if(normal==vec3(0,0,1))fakeLight=0.4;
    if(normal==vec3(-1,0,0))fakeLight=0.8;
    if(normal==vec3(1,0,0))fakeLight=0.8;
    if(normal==vec3(0,1,0))fakeLight=1.0;
    if(normal==vec3(0,-1,0))fakeLight=0.6;
    if(normal==vec3(0,0,-1))fakeLight=0.8;
    if(normal==vec3(0,0,1))fakeLight=0.8;
//    fc.xyz=.5+.5*normal;
    fc.xyz*=fakeLight;
    fc.xyz*=max(0.2,sunlight/16.0);
//    if(sunlight>=1000.0)fc.xyz*=5.0;
//    if(sunlight==0.0)fc.xyz=0.5+0.5*sin(normal);
//    if(sunlight==0.0)fc.xyz*=0.0;
}