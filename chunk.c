//
// Created by Jack Armstrong on 3/24/19.
//

#include "chunk.h"

Chunk chunk_new() {
    Chunk c;
//    printf("%p\n", &c);
    c.data = (Block *) malloc(sizeof(Block) * 16 * 256 * 16);
    for (int i = 0; i < 16 * 256 * 16; i++) {
        c.data[i] = 0;
    }
    c.max_height = 0;
    return c;
}

Block chunk_get(Chunk c, int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0 || x >= 16 || y >= 256 || z >= 16) {
        printf("Illegal chunk access at %i,%i,%i\n", x, y, z);
        return 0;
    }
    return c.data[z * 16 * 256 + y * 16 + x];
}

void chunk_set(Chunk *c, int x, int y, int z, Block b) {
    if (x < 0 || y < 0 || z < 0 || x >= 16 || y >= 256 || z >= 16) {
        printf("Illegal chunk write at %i,%i,%i and block %i\n", x, y, z, b);
        return;
    }
    c->data[z * 16 * 256 + y * 16 + x] = b;
    if (y > c->max_height)c->max_height = y;
}