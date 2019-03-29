//
// Created by Jack Armstrong on 3/27/19.
//

#ifndef GLMC_LIGHTS_H
#define GLMC_LIGHTS_H

#include "world.h"

extern int sunlight[WSIZE * 16 * 256 * WSIZE * 16];

int absorbed_sunlight(Block b);

void init_sunlight();

void sunlight_remove_block(int x, int y, int z);

void sunlight_place_block(int x, int y, int z);

int sunlight_get(int x, int y, int z);

void sunlight_set(int x, int y, int z, int i);

#endif //GLMC_LIGHTS_H
