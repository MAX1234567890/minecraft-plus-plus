//
// Created by Jack Armstrong on 3/26/19.
//

#ifndef GLMC_PHYSICS_H
#define GLMC_PHYSICS_H

#include "world.h"
#include "camera.h"
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
    float sx;
    float sy;
    float sz;
} aabb;

typedef struct {
    int x;
    int y;
    int z;
    int mode;
} CollisionResult;

aabb aabb_new(float x,float y,float z,float sx,float sy,float sz);

CollisionResult aabb_biggest_collision(aabb box);

#endif //GLMC_PHYSICS_H
