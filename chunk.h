//
// Created by Jack Armstrong on 3/24/19.
//

#ifndef GLMC_CHUNK_H
#define GLMC_CHUNK_H

#include "block.h"
#include <stdlib.h>
#include <stdio.h>
#include "perlin.h"
#include <math.h>

typedef struct {
    Block*data;
    int max_height;
} Chunk;

Chunk chunk_new();
Block chunk_get(Chunk c,int x,int y,int z);
void chunk_set(Chunk*c,int x,int y,int z,Block b);

#endif //GLMC_CHUNK_H
