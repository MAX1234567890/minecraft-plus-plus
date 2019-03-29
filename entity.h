//
// Created by Jack Armstrong on 3/26/19.
//

#ifndef GLMC_ENTITY_H
#define GLMC_ENTITY_H

#include "physics.h"

typedef struct {
    aabb box;

    //velocity
    float vx;
    float vy;
    float vz;
    float bounce;
    char*name;

    //entity-type-specific data
    void*data;

    //motion
    float mx;
    float my;
    float mz;
} Entity;

void entity_fix_velocity(Entity*e,float dt);
void entity_update(Entity*e,float dt);
void entity_player_update(Entity*e,Camera*cam,float dt);
bool entity_is_grounded(Entity e,float dt);

Entity entity_player_new();

#endif //GLMC_ENTITY_H
