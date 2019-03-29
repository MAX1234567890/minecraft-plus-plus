//
// Created by Jack Armstrong on 3/26/19.
//

#ifndef GLMC_RAYCAST_H
#define GLMC_RAYCAST_H

#include "world.h"
#include <math.h>

typedef struct {
    int x;
    int y;
    int z;
    int nx;
    int ny;
    int nz;
    bool hit;
} Intersection;

Intersection world_hit(float startX,float startY,float startZ,float dirX,float dirY,float dirZ,int range);

#endif //GLMC_RAYCAST_H
