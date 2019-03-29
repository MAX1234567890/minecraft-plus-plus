//
// Created by Jack Armstrong on 3/24/19.
//

#ifndef GLMC_CAMERA_H
#define GLMC_CAMERA_H

#include "linmath.h"
#include "input.h"
#include "config.h"
#include "utils.h"

typedef struct {
    vec3 pos;
    vec3 dir;
    float lastmx;
    float lastmy;
    float rotx;
    float roty;
} Camera;

Camera camera_new();

void camera_handle_frame(Camera*cam,float dt);

void camera_perspective(Camera cam,mat4x4 perspective);
void camera_view(Camera cam,mat4x4 view);

bool camera_can_see(Camera cam,float x,float y,float z);

#endif //GLMC_CAMERA_H
