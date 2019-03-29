#version 410 core

layout (location=0) in vec3 inPos;
layout (location=1) in vec2 inUV;
layout (location=2) in vec3 inNormal;
layout (location=3) in float inSunlight;

out vec2 uv;
out vec3 normal;
out float sunlight;

uniform float time;

uniform mat4 perspective;
uniform mat4 view;

uniform vec3 offset;

void main(){
    gl_Position=perspective*view*vec4(inPos+offset,1);
//    gl_Position.x*=cos(time);
//    gl_Position.y*=sin(time);
    uv=inUV;
    normal=inNormal;
    sunlight=inSunlight;
}