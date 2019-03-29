//
// Created by Jack Armstrong on 3/23/19.
//

#include "mesh.h"

Mesh mesh_new(){
    Mesh mesh;
    glGenVertexArrays(1,&mesh.id);

    glBindVertexArray(mesh.id);

    glGenBuffers(1,&mesh.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,0,0,GL_STATIC_DRAW);

    mesh.num=0;
    return mesh;
}

void mesh_add_buffer_2f(Mesh*mesh,GLuint attrib,float*buf,int len){
    glBindVertexArray(mesh->id);

    mesh->num=len/2;

    GLuint vbo;
    glGenBuffers(1,&vbo);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,len*sizeof(float),buf,GL_STATIC_DRAW);
    glVertexAttribPointer(attrib, 2,GL_FLOAT, GL_FALSE,0,0);
    glEnableVertexAttribArray(attrib);
}
void mesh_add_buffer_3f(Mesh*mesh,GLuint attrib,float*buf,int len){
    glBindVertexArray(mesh->id);

    mesh->num=len/3;

    GLuint vbo;
    glGenBuffers(1,&vbo);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,len*sizeof(float),buf,GL_STATIC_DRAW);
    glVertexAttribPointer(attrib,3,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(attrib);
}
void mesh_add_buffer_1i(Mesh*mesh,GLuint attrib,int*buf,int len){
    glBindVertexArray(mesh->id);
    mesh->num=len;

    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,len*sizeof(int),buf,GL_STATIC_DRAW);
    glVertexAttribPointer(attrib,1,GL_INT,GL_FALSE,0,0);
    glEnableVertexAttribArray(attrib);
}
void mesh_add_buffer_1f(Mesh*mesh,GLuint attrib,float*buf,int len){
    glBindVertexArray(mesh->id);
    mesh->num=len;

    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,len*sizeof(int),buf,GL_STATIC_DRAW);
    glVertexAttribPointer(attrib,1,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(attrib);
}
void mesh_set_indices(Mesh *mesh, unsigned int *buf, int len){
    glBindVertexArray(mesh->id);

    mesh->num=len;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,len*sizeof(unsigned int),buf,GL_STATIC_DRAW);
}
void mesh_render_elements(Mesh*mesh,GLuint mode){
    glBindVertexArray(mesh->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh->ebo);
    glDrawElements(mode,mesh->num,GL_UNSIGNED_BYTE,0);
}
void mesh_render_arrays(Mesh*mesh,GLuint mode){
    glBindVertexArray(mesh->id);

    glDrawArrays(mode,0,mesh->num);
}

Mesh mesh_box_lines(){
    Mesh m;

    float pos[]={
            0,0,0,
            1,0,0,

            1,0,0,
            1,1,0,

            1,1,0,
            0,1,0,

            0,1,0,
            0,0,0,



            0,0,1,
            1,0,1,

            1,0,1,
            1,1,1,

            1,1,1,
            0,1,1,

            0,1,1,
            0,0,1,



            0,0,0,
            0,0,1,


            1,0,0,
            1,0,1,


            0,1,0,
            0,1,1,


            1,1,0,
            1,1,1
    };
    mesh_add_buffer_3f(&m,0,pos,72);

    return m;
}