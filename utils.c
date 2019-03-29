//
// Created by Jack Armstrong on 3/26/19.
//

#include "utils.h"

void rotateX(vec3 out, const vec3 v,float theta){
    float ct= cosf(theta);
    float st= sinf(theta);

    float x=v[0];
    float y=v[1];
    float z=v[2];

    out[0]=x;
    out[1]=y*ct-z*st;
    out[2]=y*st+z*ct;
}
void rotateY(vec3 out, const vec3 v,float theta){
    float ct= cosf(theta);
    float st= sinf(theta);

    float x=v[0];
    float y=v[1];
    float z=v[2];

    out[0]=x*ct+z*st;
    out[1]=y;
    out[2]=-x*st+z*ct;
}
