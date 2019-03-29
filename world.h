//
// Created by Jack Armstrong on 3/24/19.
//

#ifndef GLMC_WORLD_H
#define GLMC_WORLD_H

#include "chunk.h"
#include "config.h"
#include <time.h>

//Chunk world[WSIZE][WSIZE];
extern Chunk** world;
extern bool pending_mesh[WSIZE][16][WSIZE];

int world_chunk_coord(int v);
int pos_in_chunk(int v);

void world_init();
Block world_get(int x,int y,int z);
void world_set(int x,int y,int z,Block b);
void world_remesh(int cx,int cy,int cz);
void world_free();

#endif //GLMC_WORLD_H
