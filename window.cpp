//
// Created by Jack Armstrong on 3/22/19.
//

#include "window.h"
GLFWwindow* window;
float window_aspect;
float window_mouse_x;
float window_mouse_y;

static void on_glfw_error(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void window_init(){
    glfwSetErrorCallback(on_glfw_error);
    if(!glfwInit()){
        printf("GLFW not initialized.\n");
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window=glfwCreateWindow(1,1,"",NULL,NULL);
}
void window_set_title(char*title){
    glfwSetWindowTitle(window,title);
}
void window_set_size(int w,int h){
    glfwSetWindowSize(window,w,h);
}
void window_set_pos(int x,int y){
    glfwSetWindowPos(window,x,y);
}


void window_hide_mouse(){
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
}
void window_release_mouse(){
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
}

void window_ready_gl(){
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);
}

bool window_alive(){
    return !glfwWindowShouldClose(window);
}

void window_wrap_frame(){
    glfwSwapBuffers(window);
    glfwPollEvents();
    if(!_window_has_moved){
        window_set_pos(150,150);
        _window_has_moved=true;
    }
    int w,h;
    glfwGetFramebufferSize(window,&w,&h);
    window_aspect=((float)w)/((float)h);

    double x,y;
    glfwGetCursorPos(window,&x,&y);
    window_mouse_x= (float) x;
    window_mouse_y= (float) y;
}

void window_end(){
    glfwTerminate();
}


float window_time(){
    return (float)glfwGetTime();
}


