#version 410 core

layout (location=0) in vec3 inPos;

uniform mat4 perspective;
uniform mat4 view;

uniform vec3 offset;

void main(){
    vec3 p=inPos;
    float scale=0.01;
    p*=(1.+2.*scale);
    p-=scale;
    gl_Position=perspective*view*vec4(p+offset, 1);
}