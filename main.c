
#include "gl.h"
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "input.h"
#include "texture.h"
#include "chunk.h"
#include "chunk_mesher.h"
#include "world.h"
#include "camera.h"
#include "entity.h"
#include "physics.h"
#include "raycast.h"
#include "lights.h"
#include <signal.h>

// 0 = false
// other = true

Entity player;

Mesh meshes[WSIZE][16][WSIZE];

//void on_key(GLFWwindow*window,int key,int scancode,int action,int mods){
//    if(action==GLFW_PRESS&&!FLY){
//        player.vy+=10;
//    }
//}

void sig_handler(int sig){
    printf("Oh noes: signal %i was sent.\n",sig);
    world_free();
    exit(EXIT_FAILURE);
}

int main(void) {
    signal(SIGSEGV,sig_handler);

    window_init();
    window_set_size(1000, 800);
    window_set_title("GLMC");

//    glfwSetKeyCallback(window,on_key);

    window_ready_gl();

    printf("MAIN: Window initialized\n");

    world_init();

    printf("MAIN: World initialized\n");

    init_sunlight();

    printf("MAIN: Sunlight initialized\n");

    Shader shader = shader_new("chunk");

    Texture  texture=texture_new("atlas-02.png",false);

    Camera camera=camera_new();

    player=entity_player_new();
    printf("%s\n",player.name);

    float time=window_time();

    gl_check_error();

    Mesh sel_block_mesh=mesh_box_lines();
    Shader sel_block_shader=shader_new("sel-block");

    float last_world_change=window_time();

    printf("MAIN: Basic GL set up\n");

    for(int x=0;x<WSIZE;x++){
        for(int y=0;y<16;y++){
            for(int z=0;z<WSIZE;z++){
                if(pending_mesh[x][y][z]){
                    pending_mesh[x][y][z]=false;
                    meshes[x][y][z]=mesh_chunk_section(world[x][z],x,z,y);
                }
            }
        }
    }

    printf("MAIN: Chunks meshed\n");

    while (window_alive()) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glGetError();

        float newTime=window_time();
        float dt=newTime-time;
        time=newTime;

        glViewport(0, 0, width, height);
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

//        camera_handle_frame(&camera,dt);

        mat4x4 perspective;
        mat4x4 view;

        camera_perspective(camera,perspective);
        camera_view(camera,view);

        shader_bind(shader);
        shader_set_4x4f(shader, "perspective", perspective);
        shader_set_4x4f(shader, "view", view);

        texture_bind(texture,0);
        shader_set_1i(shader,"tex",0);

        for(int x=0;x<WSIZE;x++){
            for(int y=0;y<16;y++){
                for(int z=0;z<WSIZE;z++){
                    vec3 p={x*16,0,z*16};
                    bool render=false;
                    for(int ox=0;ox<=1;ox++){
                        for(int oy=0;oy<=1;oy++){
                            for(int oz=0;oz<=1;oz++){
                                if(camera_can_see(camera,x*16+ox*16,y*16+oy*16,z*16+oz*16)){
                                    render=true;
                                }
                            }
                        }
                    }
                    if(render){
                        shader_set_3f(shader, "offset", x * 16, 0, z * 16);
                        mesh_render_arrays(&meshes[x][y][z], TRIANGLES);
                    }
                }
            }
        }

        entity_player_update(&player,&camera,dt);

        Intersection intersection=world_hit(camera.pos[0],camera.pos[1],camera.pos[2],camera.dir[0],camera.dir[1],camera.dir[2],50);
        if(intersection.hit){
            shader_bind(sel_block_shader);
            shader_set_4x4f(sel_block_shader,"perspective",perspective);
            shader_set_4x4f(sel_block_shader,"view",view);
            shader_set_3f(sel_block_shader,"offset",intersection.x,intersection.y,intersection.z);
            mesh_render_arrays(&sel_block_mesh,LINES);
//            printf("%i,%i,%i\n",intersection.x,intersection.y,intersection.z);
        }

        for(int x=0;x<WSIZE;x++){
            for(int y=0;y<16;y++){
                for(int z=0;z<WSIZE;z++){
                    if(pending_mesh[x][y][z]){
                        pending_mesh[x][y][z]=false;
                        meshes[x][y][z]=mesh_chunk_section(world[x][z],x,z,y);
                    }
                }
            }
        }

        if(window_time()-last_world_change>0.1&&intersection.hit){
            if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)){
                world_set(intersection.x,intersection.y,intersection.z,0);
                int cx=intersection.x/16;
                int cy=intersection.y/16;
                int cz=intersection.z/16;

                int px=intersection.x-cx*16;
                int py=intersection.y-cy*16;
                int pz=intersection.z-cz*16;

//                meshes[cx][cy][cz]=mesh_chunk_section(world[cx][cz],cx,cz,cy);

                pending_mesh[cx][cy][cz]=true;
                if(px==0)world_remesh(cx-1,cy,cz);
                if(py==0)world_remesh(cx,cy-1,cz);
                if(pz==0)world_remesh(cx,cy,cz-1);
                if(px==15)world_remesh(cx+1,cy,cz);
                if(py==15)world_remesh(cx,cy+1,cz);
                if(pz==15)world_remesh(cx,cy,cz+1);

                sunlight_remove_block(intersection.x,intersection.y,intersection.z);

                last_world_change=window_time();
            }
            if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT)){
                int x=intersection.x+intersection.nx;
                int y=intersection.y+intersection.ny;
                int z=intersection.z+intersection.nz;
                world_set(x,y,z,Cobblestone);
                sunlight_place_block(x,y,z);

                int cx=x/16;
                int cy=y/16;
                int cz=z/16;
                pending_mesh[cx][cy][cz]=true;


                last_world_change=window_time();
            }
        }

        gl_check_error();

        window_wrap_frame();
    }

    world_free();

    window_end();
    return 0;

}