//
// Created by Jack Armstrong on 3/24/19.
//

#ifndef GLMC_BLOCK_H
#define GLMC_BLOCK_H

#include <stdbool.h>
#include "config.h"

typedef int Block;

enum {
    Grass=1,
    Dirt=2,
    Stone=3,
    Wood=4,
    Leaf=5,
    Cobblestone=6
};

//typedef bool(*block_to_bool)(Block b);
//typedef int(*block_to_int)(Block b);

enum {
    CollisionNone=0,
    CollisionFull=1
};

bool block_is_transparent(Block b);
int block_collision_mode(Block b);

#endif //GLMC_BLOCK_H
