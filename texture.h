//
// Created by Jack Armstrong on 3/24/19.
//

#ifndef GLMC_TEXTURE_H
#define GLMC_TEXTURE_H

#include "gl.h"
#include "stb_image.h"
#include <string.h>
#include <stdbool.h>

typedef GLuint Texture;

Texture texture_new(char*fn,bool flip);

void texture_bind(Texture t,int unit);

#endif //GLMC_TEXTURE_H
