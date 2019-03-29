//
// Created by Jack Armstrong on 3/24/19.
//

#ifndef GLMC_CHUNK_MESHER_H
#define GLMC_CHUNK_MESHER_H

#include "gl.h"
#include "chunk.h"
#include "block.h"
#include "mesh.h"
#include <stdbool.h>
#include "world.h"
#include "config.h"
#include "lights.h"

typedef struct {
    float x;
    float y;
    float w;
    float h;
} AtlasPos;

#define apGrassTop ap_new(0,0,16,16)
#define apGrassSide ap_new(3,0,16,16)
#define apDirt ap_new(2,0,16,16)
#define apStone ap_new(1,0,16,16)
#define apAll ap_new(0,0,1,1)
#define apWoodSide ap_new(4,1,16,16)
#define apWoodTop ap_new(5,1,16,16)
#define apLeaf ap_new(4+!TRANSPARENT_LEAF,3,16,16)
#define apCobblestone ap_new(0,1,16,16)

AtlasPos ap_new(float tx,float ty,float aw,float ah);

AtlasPos ap_xmi(Block b);
AtlasPos ap_xpl(Block b);
AtlasPos ap_ymi(Block b);
AtlasPos ap_ypl(Block b);
AtlasPos ap_zmi(Block b);
AtlasPos ap_zpl(Block b);

bool display_xmi(Block adjacent,Block self);
bool display_xpl(Block adjacent,Block self);
bool display_ymi(Block adjacent,Block self);
bool display_ypl(Block adjacent,Block self);
bool display_zmi(Block adjacent,Block self);
bool display_zpl(Block adjacent,Block self);

Mesh mesh_chunk_section(Chunk chunk,int chunkX,int chunkZ,int sectionY);


#endif //GLMC_CHUNK_MESHER_H
