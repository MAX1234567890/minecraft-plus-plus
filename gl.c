//
// Created by Jack Armstrong on 3/24/19.
//

#include "gl.h"

void gl_check_error(){
    GLuint code=glGetError();
    switch(code){
        case GL_NO_ERROR:
            break;
        case GL_INVALID_ENUM:
            printf("OPENGL ERROR: Invalid Enum\n");
            break;
        case GL_INVALID_VALUE:
            printf("OPENGL ERROR: Invalid Value\n");
            break;
        case GL_INVALID_OPERATION:
            printf("OPENGL ERROR: Invalid Operation\n");
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            printf("OPENGL ERROR: Invalid Framebuffer Operation\n");
            break;
        case GL_OUT_OF_MEMORY:
            printf("OPENGL ERROR: Out of Memory\n");
            break;
//        case :
//            printf
    }
}
