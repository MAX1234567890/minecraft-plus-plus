//
// Created by Jack Armstrong on 3/26/19->
//

#include "entity.h"


void entity_fix_velocity(Entity*e,float dt){

    float rvx=e->vx+e->mx;
    float rvy=e->vy+e->my;
    float rvz=e->vz+e->mz;

    rvx*=dt;
    rvy*=dt;
    rvz*=dt;

    e->box.x+=rvx;
    if(aabb_biggest_collision(e->box).mode>0){
        e->box.x-=rvx;
        e->vx*=e->bounce;
    }

    e->box.y+=rvy;
    if(aabb_biggest_collision(e->box).mode>0){
        e->box.y-=rvy;
        e->vy*=e->bounce;
    }

    e->box.z+=rvz;
    if(aabb_biggest_collision(e->box).mode>0){
        e->box.z-=rvz;
        e->vz*=e->bounce;
    }
}

bool entity_is_grounded(Entity e,float dt){
//    e.box.y=ceil(e.box.y);
    e.vx=e.vz=0;
    e.vy=-1;
    entity_fix_velocity(&e,dt);
    return e.vy!=-1;
}

void entity_update(Entity*e,float dt){
    entity_fix_velocity(e,dt);
    if(!FLY)e->vy+=GRAVITY*dt;
}

void entity_player_update(Entity*e,Camera*cam,float dt){
    entity_update(e,dt);
    window_hide_mouse();
    float forward_speed=5;
    float side_speed=4;
    float back_speed=3;
    float up_speed=4;
    float down_speed=4;//TODO: make speed a property of camera
    vec3 forward={0,0,0};
    vec3_add(forward,  forward,cam->dir);
    forward[1]=0;
    vec3_norm(forward,forward);
    vec3_scale(forward,  forward,forward_speed);
    forward[1]=0;

    vec3 backward={0,0,0};
    vec3_add(backward, backward,cam->dir);
    backward[1]=0;
    vec3_norm(backward,backward);
    vec3_scale(backward,  backward,-back_speed);
    backward[1]=0;

    vec3 right={0,0,0};
    vec3_add(right,   right,cam->dir);
    right[1]=0;
    vec3_norm(right,right);
    vec3_scale(right,  right,side_speed);
    right[1]=0;

    vec3 up={0,up_speed*dt,0};
    vec3 down={0,-down_speed*dt,0};

    rotateY(right, right,-M_PI/2);

    vec3 motion={0,0,0};

    if(is_key_down('A')){
        vec3_sub(motion,  motion,right);
    }
    if(is_key_down('D')){
        vec3_add(motion,  motion,right);
    }
    if(is_key_down('W')){
        vec3_add(motion,  motion,forward);
    }
    if(is_key_down('S')){
        vec3_add(motion,  motion,backward);
    }
    if(FLY) {
        if (is_key_down(' ')) {
            vec3_add(motion, motion, up);
        }
        if (is_key_down(GLFW_KEY_LEFT_SHIFT)) {
            vec3_add(motion, motion, down);
        }
    }else{
        if(is_key_down(' ')&&entity_is_grounded(*e,dt)){
//            e->vy+=(100-GRAVITY)*dt;
            e->vy+=15;
        }
    }
    if(is_key_down(GLFW_KEY_LEFT_CONTROL)){
        vec3_scale(motion,motion,FLY?10:2);
    }
//    vec3_scale(motion,motion,0.1);
    e->mx=motion[0];
    e->my=motion[1];
    e->mz=motion[2];
//    vec3_add(cam->pos, cam->pos,motion);


    float new_mx=window_mouse_x;
    float new_my=window_mouse_y;

    float dx=cam->lastmx-new_mx;
    float dy=cam->lastmy-new_my;

    cam->lastmx=new_mx;
    cam->lastmy=new_my;

    cam->dir[0]=0;
    cam->dir[1]=0;
    cam->dir[2]=1;

    cam->rotx-=dy*2*dt;
    cam->roty+=dx*2*dt;

    float c=0.49*M_PI;
    if(cam->rotx>c)cam->rotx=c;
    if(cam->rotx<-c)cam->rotx=-c;

    rotateX(cam->dir,  cam->dir,cam->rotx);
    rotateY(cam->dir,  cam->dir,cam->roty);

    cam->pos[0]=e->box.x+e->box.sx/2;
    cam->pos[1]=e->box.y+e->box.sy*.9;
    cam->pos[2]=e->box.z+e->box.sz/2;
}

Entity entity_player_new(){
    Entity e;
    e.box=aabb_new(WSIZE*8,128,WSIZE*8,.9,1.9,.9);
    e.bounce=0;
    e.data=0;
    e.name="PLAYER";
    e.vx=0;
    e.vy=0;
    e.vz=0;
    return e;
}