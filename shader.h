//
// Created by Jack Armstrong on 3/23/19.
//

#ifndef GLMC_SHADER_H
#define GLMC_SHADER_H

#include "gl.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory.h>
#include "linmath.h"

typedef GLuint Shader;

Shader shader_new(const std::string& name);

void shader_bind(Shader sh);

void shader_set_1f(Shader sh, std::string name, float x);

void shader_set_3f(Shader sh, std::string name, float x, float y, float z);

void shader_set_1i(Shader sh, std::string name, int x);

void shader_set_4x4f(Shader sh, std::string name, mat4x4 m);

#endif //GLMC_SHADER_H
