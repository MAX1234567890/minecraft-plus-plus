//
// Created by Jack Armstrong on 3/24/19.
//

#include "world.h"
#include "chunk.h"

Chunk** world;
bool pending_mesh[WSIZE][16][WSIZE];

int world_chunk_coord(int v){
    return v/16;
}

int pos_in_chunk(int v){
    return v-16*world_chunk_coord(v);
}

void world_remesh(int cx,int cy,int cz){
    if(cx>=0&&cx<WSIZE&&cy>=0&&cy<15&&cz>=0&&cz<WSIZE)pending_mesh[cx][cy][cz]=true;
}

void world_init(){
    world=(Chunk**)malloc(WSIZE*WSIZE*sizeof(Chunk));
    if(world==0){
        printf("World memory not allocated :(\n");
        exit(EXIT_FAILURE);
    }
    for(int x=0;x<WSIZE;x++){
        world[x]=(Chunk*)malloc(WSIZE*sizeof(Chunk));
        for(int z=0;z<WSIZE;z++){
            world[x][z]=chunk_new();//TODO: world generation here
            for(int y=0;y<16;y++){
                pending_mesh[x][y][z]=true;
            }
        }
    }

//    srand(time(0));

    int seed= (int) time(0);

    int randi=0;

    float small_zoom=0.01;
    float med_zoom=0.05;
    float big_zoom=0.05;
    float tree_zoom=0.05;

    float scale=1;
    small_zoom*=scale;
    med_zoom*=scale;
    big_zoom*=scale;

    float perst=0.75;
    int oct=3;

    float tree_leaf_layout[4][5][5]={
            {
                    {.5,1,1,1,.5},
                    {1,1,1,1,1},
                    {1,1,1,1,1},
                    {1,1,1,1,1},
                    {.5,1,1,1,.5}
            },
            {
                    {.25,1,1,1,.25},
                    {1,1,1,1,1},
                    {1,1,1,1,1},
                    {1,1,1,1,1},
                    {.25,1,1,1,.25}
            },
            {
                    {0,0,0,0,0},
                    {0,.5,1,.5,0},
                    {0,1,1,1,0},
                    {0,.5,1,.5,0},
                    {0,0,0,0,0}
            },
            {
                    {0,0,0,0,0},
                    {0,0,1,0,0},
                    {0,1,1,1,0},
                    {0,0,1,0,0},
                    {0,0,0,0,0}
            }
    };

    for(int x=0;x<WSIZE*16;x++){
        for(int z=0;z<WSIZE*16;z++){
            float elev=(smooth2d(x*small_zoom,z*small_zoom,0,seed)*.5+.5);
            float rough=(smooth2d(x*med_zoom,z*med_zoom,1,seed)*.5+.5);
            float detail=(smooth2d(x*big_zoom,z*big_zoom,2,seed)*.5+.5)*.1;
//            float elev=pnoise2d(x*small_zoom,z*small_zoom,perst,oct,seed);
//            float rough=pnoise2d(x*med_zoom,z*med_zoom,perst,oct,seed);
//            float detail=pnoise2d(x*big_zoom,z*big_zoom,perst,oct,seed);
            float fh=(elev+rough*detail)*64+64;
            int h=(int)fh;
//            int h=20+(int)(10*smooth2d(x*0.1,z*0.1,0,seed));
            for(int y=0;y<=h;y++){
                if(y<h-4)world_set(x,y,z,Stone);
                else if(y<h)world_set(x,y,z,Dirt);
                else world_set(x,y,z,Grass);
            }

            float tree_chance=smooth2d(x*tree_zoom,z*tree_zoom,3,seed);
//            if(tree_chance>-.99)tree_chance= -.99;
            if(tree_chance>0)tree_chance=tree_chance*.2-1;
            else if(tree_chance<0)tree_chance=-1;

            if(rawnoise(randi++)<tree_chance){
                int tree_height=5+(int)round(rawnoise(randi++));
                for(int i=h+1;i<h+tree_height;i++){
                    world_set(x,i,z,Wood);
                }
//                for(int ox=-1;ox<=1;ox++){
//                    for(int oy=-1;oy<=1;oy++){
//                        for(int oz=-1;oz<=1;oz++){
//                            int rx=x+ox;
//                            int ry=h+5+oy;
//                            int rz=z+oz;
//                            if(world_get(rx,ry,rz)==0){
//                                world_set(rx,ry,rz,Leaf);
//                            }
//                        }
//                    }
//                }
                for(int ox=-2;ox<=2;ox++){
                    for(int oy=0;oy<4;oy++){
                        for(int oz=-2;oz<=2;oz++){
                            if(rawnoise(randi++)*.5+.5<tree_leaf_layout[oy][ox+2][oz+2]){
                                int rx=x+ox;
                                int ry=h+tree_height-2+oy;
                                int rz=z+oz;
                                if(world_get(rx,ry,rz)==0){
                                    world_set(rx,ry,rz,Leaf);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
Block world_get(int x,int y,int z){
    if(x<0||y<0||z<0||x>=16*WSIZE||y>=256||z>=16*WSIZE)return 0;
    return chunk_get(world[world_chunk_coord(x)][world_chunk_coord(z)],pos_in_chunk(x),y,pos_in_chunk(z));
}
void world_set(int x,int y,int z,Block b){
    if(x<0||y<0||z<0||x>=16*WSIZE||y>=256||z>=16*WSIZE)return;
    chunk_set(&world[world_chunk_coord(x)][world_chunk_coord(z)],pos_in_chunk(x),y,pos_in_chunk(z),b);
}

void world_free(){
    if(world!=0){
        for(int x=0;x<WSIZE;x++){
            for(int z=0;z<WSIZE;z++){
                free(world[x][z].data);
            }
            free(world[x]);
        }
        free(world);
    }
}