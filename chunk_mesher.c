//
// Created by Jack Armstrong on 3/24/19.
//

#include "chunk_mesher.h"

AtlasPos ap_new(float tx,float ty,float aw,float ah){
    AtlasPos ap;
    ap.x=tx/aw;
    ap.y=ty/ah;
    ap.w=1/aw;
    ap.h=1/ah;
    return ap;
}

AtlasPos ap_xmi(Block b){
    switch(b){
        case Grass:
            return apGrassSide;
        case Dirt:
            return apDirt;
        case Stone:
            return apStone;
        case Wood:
            return apWoodSide;
        case Leaf:
            return apLeaf;
        case Cobblestone:
            return apCobblestone;
    }
    return apAll;
}
AtlasPos ap_xpl(Block b){
    switch(b){
        case Grass:
            return apGrassSide;
        case Dirt:
            return apDirt;
        case Stone:
            return apStone;
        case Wood:
            return apWoodSide;
        case Leaf:
            return apLeaf;
        case Cobblestone:
            return apCobblestone;
    }
    return apAll;
}
AtlasPos ap_ymi(Block b){
    switch(b){
        case Grass:
            return apDirt;
        case Dirt:
            return apDirt;
        case Stone:
            return apStone;
        case Wood:
            return apWoodTop;
        case Leaf:
            return apLeaf;
        case Cobblestone:
            return apCobblestone;
    }
    return apAll;
}
AtlasPos ap_ypl(Block b){
    switch(b){
        case Grass:
            return apGrassTop;
        case Dirt:
            return apDirt;
        case Stone:
            return apStone;
        case Wood:
            return apWoodTop;
        case Leaf:
            return apLeaf;
        case Cobblestone:
            return apCobblestone;
    }
    return apAll;
}
AtlasPos ap_zmi(Block b){
    switch(b){
        case Grass:
            return apGrassSide;
        case Dirt:
            return apDirt;
        case Stone:
            return apStone;
        case Wood:
            return apWoodSide;
        case Leaf:
            return apLeaf;
        case Cobblestone:
            return apCobblestone;
    }
    return apAll;
}
AtlasPos ap_zpl(Block b){
    switch(b){
        case Grass:
            return apGrassSide;
        case Dirt:
            return apDirt;
        case Stone:
            return apStone;
        case Wood:
            return apWoodSide;
        case Leaf:
            return apLeaf;
        case Cobblestone:
            return apCobblestone;
    }
    return apAll;
}

bool display_xmi(Block adjacent,Block self){
    if(!block_is_transparent(self) && block_is_transparent(adjacent))return true;
//    if(block_is_transparent(self) && block_is_transparent(adjacent) && self == adjacent)return false;
    return block_is_transparent(adjacent);
}

bool display_xpl(Block adjacent,Block self){
    if(!block_is_transparent(self) && block_is_transparent(adjacent))return true;
//    if(block_is_transparent(self) && block_is_transparent(adjacent) && self == adjacent)return false;
    return block_is_transparent(adjacent);
}

bool display_ymi(Block adjacent,Block self){
    if(!block_is_transparent(self) && block_is_transparent(adjacent))return true;
//    if(block_is_transparent(self) && block_is_transparent(adjacent) && self == adjacent)return false;
    return block_is_transparent(adjacent);
}

bool display_ypl(Block adjacent,Block self){
    if(!block_is_transparent(self) && block_is_transparent(adjacent))return true;
//    if(block_is_transparent(self) && block_is_transparent(adjacent) && self == adjacent)return false;
    return block_is_transparent(adjacent);
}

bool display_zmi(Block adjacent,Block self){
    if(!block_is_transparent(self) && block_is_transparent(adjacent))return true;
//    if(block_is_transparent(self) && block_is_transparent(adjacent) && self == adjacent)return false;
    return block_is_transparent(adjacent);
}

bool display_zpl(Block adjacent,Block self){
    if(!block_is_transparent(self) && block_is_transparent(adjacent))return true;
//    if(block_is_transparent(self) && block_is_transparent(adjacent) && self == adjacent)return false;
    return block_is_transparent(adjacent);
}

Mesh mesh_chunk_section(Chunk chunk,int chunkX,int chunkZ,int sectionY){
    int numPos=0;
    int numUV=0;
    int numNorm=0;
    int numSunlight=0;

    for(int x=0;x<16;x++){
        for(int y=sectionY*16;y<sectionY*16+16;y++){
            for(int z=0;z<16;z++){
                Block block=chunk_get(chunk, x,y,z);
                if(block != 0){
                    int rx=x+chunkX*16;
                    int rz=z+chunkZ*16;
                    if(display_xmi(world_get(rx-1,y,rz),block)) {
                        numPos += 6;
                        numUV += 6;
                        numNorm+=6;
                        numSunlight+=6;
                    }
                    if(display_xpl(world_get(rx+1,y,rz),block)){
                        numPos+=6;
                        numUV+=6;
                        numNorm+=6;
                        numSunlight+=6;
                    }
                    if(display_ymi(world_get(rx,y-1,rz),block)) {
                        numPos += 6;
                        numUV += 6;
                        numNorm+=6;
                        numSunlight+=6;
                    }
                    if(display_ypl(world_get(rx,y+1,rz),block)){
                        numPos+=6;
                        numUV+=6;
                        numNorm+=6;
                        numSunlight+=6;
                    }
                    if(display_zmi(world_get(rx,y,rz-1),block)) {
                        numPos += 6;
                        numUV += 6;
                        numNorm+=6;
                        numSunlight+=6;
                    }
                    if(display_zpl(world_get(rx,y,rz+1),block)){
                        numPos+=6;
                        numUV+=6;
                        numNorm+=6;
                        numSunlight+=6;
                    }
                }
            }
        }
    }

    float pos[numPos*3];
    float uv[numUV*2];
    float norm[numNorm*3];
    float sun[numSunlight];

    int p_i=0;
    int u_i=0;
    int n_i=0;
    int s_i=0;

    for(int x=0;x<16;x++){
        for(int y=sectionY*16;y<sectionY*16+16;y++){
            for(int z=0;z<16;z++){
                Block block=chunk_get(chunk, x,y,z);
                if(block!=0) {
                    int rx=x+chunkX*16;
                    int rz=z+chunkZ*16;
                    if(display_xmi(world_get(rx-1,y,rz),block)) {
                        AtlasPos ap=ap_xmi(block);
                        pos[p_i++] = x;
                        pos[p_i++] = y;
                        pos[p_i++] = z;

                        pos[p_i++] = x;
                        pos[p_i++] = y;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x;
                        pos[p_i++] = y+1;
                        pos[p_i++] = z;

                        pos[p_i++] = x;
                        pos[p_i++] = y;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x;
                        pos[p_i++] = y+1;
                        pos[p_i++] = z;

                        pos[p_i++] = x;
                        pos[p_i++] = y + 1;
                        pos[p_i++] = z+1;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y;

                        for(int i=0;i<6;i++){
                            norm[n_i++]=-1;
                            norm[n_i++]=0;
                            norm[n_i++]=0;
                            sun[s_i++]=sunlight_get(rx-1,y,rz);
                        }
                    }
                    if(display_xpl(world_get(rx+1,y,rz),block)) {
                        AtlasPos ap=ap_xpl(block);
                        pos[p_i++] = x+1;
                        pos[p_i++] = y;
                        pos[p_i++] = z;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y+1;
                        pos[p_i++] = z;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y+1;
                        pos[p_i++] = z;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y + 1;
                        pos[p_i++] = z+1;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y;

                        for(int i=0;i<6;i++){
                            norm[n_i++]=1;
                            norm[n_i++]=0;
                            norm[n_i++]=0;
                            sun[s_i++]=sunlight_get(rx+1,y,rz);
                        }
                    }
                    if(display_ymi(world_get(rx,y-1,rz),block)) {
                        AtlasPos ap=ap_ymi(block);
                        pos[p_i++] = x;
                        pos[p_i++] = y;
                        pos[p_i++] = z;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y;
                        pos[p_i++] = z;

                        pos[p_i++] = x;
                        pos[p_i++] = y;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y;
                        pos[p_i++] = z;

                        pos[p_i++] = x;
                        pos[p_i++] = y;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y;
                        pos[p_i++] = z+1;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y;

                        for(int i=0;i<6;i++){
                            norm[n_i++]=0;
                            norm[n_i++]=-1;
                            norm[n_i++]=0;
                            sun[s_i++]=sunlight_get(rx,y-1,rz);
                        }
                    }
                    if(display_ypl(world_get(rx,y+1,rz),block)) {
                        AtlasPos ap=ap_ypl(block);
                        pos[p_i++] = x;
                        pos[p_i++] = y+1;
                        pos[p_i++] = z;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y+1;
                        pos[p_i++] = z;

                        pos[p_i++] = x;
                        pos[p_i++] = y+1;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y+1;
                        pos[p_i++] = z;

                        pos[p_i++] = x;
                        pos[p_i++] = y+1;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x+1;
                        pos[p_i++] = y+1;
                        pos[p_i++] = z+1;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y;

                        for(int i=0;i<6;i++){
                            norm[n_i++]=0;
                            norm[n_i++]=1;
                            norm[n_i++]=0;
                            sun[s_i++]=sunlight_get(rx,y+1,rz);
                        }
                    }
                    if(display_zmi(world_get(rx,y,rz-1),block)) {
                        AtlasPos ap=ap_zmi(block);
                        pos[p_i++] = x;
                        pos[p_i++] = y;
                        pos[p_i++] = z;

                        pos[p_i++] = x + 1;
                        pos[p_i++] = y;
                        pos[p_i++] = z;

                        pos[p_i++] = x;
                        pos[p_i++] = y + 1;
                        pos[p_i++] = z;

                        pos[p_i++] = x + 1;
                        pos[p_i++] = y;
                        pos[p_i++] = z;

                        pos[p_i++] = x;
                        pos[p_i++] = y + 1;
                        pos[p_i++] = z;

                        pos[p_i++] = x + 1;
                        pos[p_i++] = y + 1;
                        pos[p_i++] = z;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y;

                        for(int i=0;i<6;i++){
                            norm[n_i++]=0;
                            norm[n_i++]=0;
                            norm[n_i++]=-1;
                            sun[s_i++]=sunlight_get(rx,y,rz-1);
                        }
                    }
                    if(display_zpl(world_get(rx,y,rz+1),block)) {
                        AtlasPos ap=ap_zpl(block);
                        pos[p_i++] = x;
                        pos[p_i++] = y;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x + 1;
                        pos[p_i++] = y;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x;
                        pos[p_i++] = y + 1;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x + 1;
                        pos[p_i++] = y;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x;
                        pos[p_i++] = y + 1;
                        pos[p_i++] = z+1;

                        pos[p_i++] = x + 1;
                        pos[p_i++] = y + 1;
                        pos[p_i++] = z+1;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y+ap.h;

                        uv[u_i++] = ap.x;
                        uv[u_i++] = ap.y;

                        uv[u_i++] = ap.x+ap.w;
                        uv[u_i++] = ap.y;

                        for(int i=0;i<6;i++){
                            norm[n_i++]=0;
                            norm[n_i++]=0;
                            norm[n_i++]=1;
                            sun[s_i++]=sunlight_get(rx,y,rz+1);
                        }
                    }
                }
            }
        }
    }

    Mesh mesh=mesh_new();
    mesh_add_buffer_3f(&mesh,0,pos,numPos*3);
    mesh_add_buffer_2f(&mesh,1,uv,numUV*2);
    mesh_add_buffer_3f(&mesh,2,norm,numNorm*3);
    mesh_add_buffer_1f(&mesh,3,sun,numSunlight);
//    mesh_set_indices(&mesh, tri, numTri * 3);

    return mesh;
}