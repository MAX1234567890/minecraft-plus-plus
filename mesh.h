//
// Created by Jack Armstrong on 3/23/19.
//

#ifndef GLMC_MESH_H
#define GLMC_MESH_H

#include "gl.h"

//typedef GLuint Mesh;
typedef struct {
    GLuint id;
    int num;
    GLuint ebo;
} Mesh;

#define TRIANGLES GL_TRIANGLES
#define LINES GL_LINES

Mesh mesh_new();
void mesh_add_buffer_2f(Mesh*mesh,GLuint attrib,float*buf,int len);
void mesh_add_buffer_3f(Mesh*mesh,GLuint attrib,float*buf,int len);
void mesh_add_buffer_1f(Mesh*mesh,GLuint attrib,float*buf,int len);
void mesh_add_buffer_1i(Mesh*mesh,GLuint attrib,int*buf,int len);
void mesh_set_indices(Mesh *mesh, unsigned int *buf, int len);
void mesh_render_elements(Mesh*mesh,GLuint mode);
void mesh_render_arrays(Mesh*mesh,GLuint mode);

Mesh mesh_box_lines();

#endif //GLMC_MESH_H
