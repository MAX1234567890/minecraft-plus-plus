//
// Created by Jack Armstrong on 3/26/19.
//

#include "physics.h"

#ifdef linux
float floorf(float f) {
    return (int)f;
}
#endif

CollisionResult aabb_biggest_collision(aabb box){
    int x0= (int) floorf(box.x);
    int y0= (int) floorf(box.y);
    int z0= (int) floorf(box.z);
    int x1= (int) floorf(box.x + box.sx);
    int y1= (int) floorf(box.y + box.sy);
    int z1= (int) floorf(box.z + box.sz);

    CollisionResult res;
    res.x=-1;
    res.y=-1;
    res.z=-1;
    res.mode=CollisionNone;
    for(int x=x0;x<=x1;x++){
        for(int y=y0;y<=y1;y++){
            for(int z=z0;z<=z1;z++) {
                int ntype = block_collision_mode(world_get(x, y, z));
                if (ntype > res.mode){
                    res.mode = ntype;
                    res.x=x;
                    res.y=y;
                    res.z=z;
                }
            }
        }
    }

    return res;
}

aabb aabb_new(float x,float y,float z,float sx,float sy,float sz){
    aabb bb;
    bb.x=x;
    bb.y=y;
    bb.z=z;
    bb.sx=sx;
    bb.sy=sy;
    bb.sz=sz;
    return bb;
}