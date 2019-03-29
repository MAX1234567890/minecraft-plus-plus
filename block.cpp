//
// Created by Jack Armstrong on 3/26/19.
//

#include "block.h"


bool block_is_transparent(Block b){
    if(b==Leaf){
        return TRANSPARENT_LEAF;
    }
    if(b==0)return true;
    return false;
}

int block_collision_mode(Block b){
    if(b==0)return CollisionNone;
    return CollisionFull;
}