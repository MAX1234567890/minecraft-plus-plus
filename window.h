//
// Created by Jack Armstrong on 3/22/19.
//

#ifndef GLMC_WINDOW_H
#define GLMC_WINDOW_H

#include "glad.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

extern GLFWwindow* window;
extern float window_aspect;
extern float window_mouse_x;
extern float window_mouse_y;
static bool _window_has_moved=false;

void window_init();
void window_set_title(char*title);
void window_set_size(int w,int h);
void window_set_pos(int x,int y);

void window_hide_mouse();
void window_release_mouse();

void window_ready_gl();

bool window_alive();

void window_wrap_frame();

void window_end();

float window_time();



#endif //GLMC_WINDOW_H
