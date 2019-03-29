//
// Created by Jack Armstrong on 3/24/19.
//

#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"

Texture texture_new(char*name,bool flip){
    Texture t;
    glGenTextures(1,&t);

//    gl_check_error();
    glBindTexture(GL_TEXTURE_2D,t);

//    gl_check_error();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//    gl_check_error();
    int w,h,ch;

    char fn[200];
    strcpy(fn,"../textures/");
    strcat(fn,name);

    stbi_set_flip_vertically_on_load(flip);
    unsigned char*pixels=stbi_load(fn,&w,&h,&ch,0);
    if(pixels==NULL){
        printf("File not found: %s\n",fn);
        exit(EXIT_FAILURE);
        return NULL;
    }

    GLenum frmt=GL_RGB;
    if(ch==4)frmt=GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
//    glGenerateMipmap(GL_TEXTURE_2D);

    gl_check_error();
    stbi_image_free(pixels);

    return t;
}

void texture_bind(Texture t,int u){
    glActiveTexture(GL_TEXTURE0+u);
    glBindTexture(GL_TEXTURE_2D,t);
}