//
// Created by Jack Armstrong on 3/24/19.
//

#include "camera.h"

Camera camera_new(){
    Camera c;
    c.pos[0]=WSIZE*8;
    c.pos[1]=128;
    c.pos[2]=WSIZE*8;

    c.dir[0]=-1;
    c.dir[1]=0;
    c.dir[2]=1;
    vec3_norm(c.dir,c.dir);

    c.lastmx=0;
    c.lastmy=0;

    c.rotx=0;
    c.roty=0;

    return c;
}

void camera_handle_frame(Camera*cam,float dt){
    window_hide_mouse();
    vec3 x_axis={1,0,0};
    vec3 y_axis={0,1,0};
    float forward_speed=5;
    float side_speed=4;
    float back_speed=3;
    float up_speed=4;
    float down_speed=4;//TODO: make speed a property of camera
    vec3 forward={0,0,0};
    vec3_add(forward,  forward,cam->dir);
    forward[1]=0;
    vec3_norm(forward,forward);
    vec3_scale(forward,  forward,forward_speed*dt);

    vec3 backward={0,0,0};
    vec3_add(backward, backward,cam->dir);
    backward[1]=0;
    vec3_norm(backward,backward);
    vec3_scale(backward,  backward,-back_speed*dt);

    vec3 right={0,0,0};
    vec3_add(right,   right,cam->dir);
    right[1]=0;
    vec3_norm(right,right);
    vec3_scale(right,  right,side_speed*dt);

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
    }
    if(is_key_down(GLFW_KEY_LEFT_CONTROL)){
        vec3_scale(motion,motion,20);
    }
    vec3_add(cam->pos, cam->pos,motion);


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
//
//    cam->rotx= (float) (window_mouse_x / 3000.0);
//    cam->roty= (float) (window_mouse_y / 3000.0);
//
//    printf("%f,%f  %f,%f  %f,%f\n",cam->rotx,cam->roty,cam->lastmx,cam->lastmy,window_mouse_x,window_mouse_y);


    rotateX(cam->dir,  cam->dir,cam->rotx);
    rotateY(cam->dir,  cam->dir,cam->roty);
}

void camera_perspective(Camera cam,mat4x4 perspective){//TODO: make fov,near,far be props of `cam`
    float fov = 1.396;
    float near=0.01;
    float far=1000;
    mat4x4_perspective(perspective,fov,window_aspect,near,far);
}

void camera_view(Camera cam,mat4x4 view){
    vec3 center={0,0,0};
    vec3_add(center,  cam.pos,cam.dir);
    vec3 up={0,1,0};
    mat4x4_look_at(view,cam.pos,center,up);
}
bool camera_can_see(Camera cam,float x,float y,float z){
    vec3 v={x,y,z};
    vec3 ab={0,0,0};
    vec3_sub(ab, v,cam.pos);
    float dot=vec3_mul_inner(ab,cam.dir);
    return dot > -0;//TODO: `&& distance(cam.pos,v) < cam.far`
}