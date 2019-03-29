//
// Created by Jack Armstrong on 3/27/19.
//

#include "lights.h"
#include "chunk.h"

int sunlight[WSIZE * 16 * 256 * WSIZE * 16];

int absorbed_sunlight(Block b) {
    if (b == 0)return 0;
    if (b == Leaf)return 2;
    return 16;
}

void init_sunlight() {
    for (int x = 0; x < WSIZE * 16; x++) {
        for (int y = 0; y < 256; y++) {
            for (int z = 0; z < WSIZE * 16; z++) {
                sunlight_set(x, y, z, -1);
            }
        }
    }

    for (int cx = 0; cx < WSIZE; cx++) {
        for (int cz = 0; cz < WSIZE; cz++) {


            Chunk c = world[cx][cz];

            for (int x = 0; x < 16; x++) {
                for (int z = 0; z < 16; z++) {
                    int y = 255;
                    int val = 16;
                    while (y >= 0) {
                        sunlight_set(cx * 16 + x, y, cz * 16 + z, val);
                        val -= absorbed_sunlight(chunk_get(c, x, y, z));
                        if (val < 0)val = 0;
                        y--;
                    }
                }
            }


        }
    }
}

void sunlight_remove_block(int x, int y, int z) {
//    while(world_get(x,y,z)==0&&y<256)y++;
    y++;
    int val = sunlight_get(x, y, z);
//    y++;
//    Chunk c=world[x/16][z/16];
    while (y >= 0) {
        sunlight_set(x, y, z, val);
        val -= absorbed_sunlight(world_get(x, y, z));
        if (val < 0)val = 0;
        y--;
    }
}

void sunlight_place_block(int x, int y, int z) {
//    y=256;
    int val = sunlight_get(x, y, z);
//    y++;
//    Chunk c=world[x/16][z/16];
    while (y >= 0) {
        sunlight_set(x, y, z, val);
        val -= absorbed_sunlight(world_get(x, y, z));
        if (val < 0)val = 0;
        y--;
    }
//    while(world_get(x,y,z)==0&&y<256)y++;
//    y-=1;
//    int val=sunlight_get(x,y,z);
//    y++;
//    Chunk c=world[x/16][z/16];
//    while(y>=0&&val>0){
//        sunlight_set(x,y,z,val);
//        val-=absorbed_sunlight(world_get(x,y,z));
//        y--;
//    }
}

int sunlight_get(int x, int y, int z) {
    if (y > world[x / 16][z / 16].max_height)return 16;
//    if(x<0||y<0||z<0||x>=WSIZE*16||y>=256||z>=WSIZE*16){
//        printf("Illegal sunlight access at %i,%i,%i\n",x,y,z);
//        return 0;
//    }
    int s = sunlight[z * WSIZE * 16 * 256 + y * WSIZE * 16 + x];
    if (s == -1)return 16;
    return s;
//    return 16;
}

void sunlight_set(int x, int y, int z, int i) {
    if (x < 0 || y < 0 || z < 0 || x >= WSIZE * 16 || y >= 256 || z >= WSIZE * 16) {
//        printf("Illegal sunlight write at %i,%i,%i and sunlight %i\n", x, y, z, i);
        return;
    }
    pending_mesh[x / 16][y / 16][z / 16] = true;
    world_remesh(x / 16 - 1, y / 16, z / 16);
    world_remesh(x / 16 + 1, y / 16, z / 16);
    world_remesh(x / 16, y / 16 - 1, z / 16);
    world_remesh(x / 16, y / 16 + 1, z / 16);
    world_remesh(x / 16, y / 16, z / 16 - 1);
    world_remesh(x / 16, y / 16, z / 16 + 1);
    sunlight[z * WSIZE * 16 * 256 + y * WSIZE * 16 + x] = i;
}