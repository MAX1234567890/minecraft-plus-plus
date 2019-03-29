//
// Created by Jack Armstrong on 3/23/19.
//

#include "shader.h"

Shader shader_new(const std::string& name) {
    std::string vertFileName = "../shaders/" + name + ".vert";
    // lol cuz the executable is in cmake-build-debug
    std::ifstream vertFile(vertFileName);
    if (vertFile.bad()) {
        std::cout << "FILE " << vertFileName << " NOT FOUND.\n";
        exit(EXIT_FAILURE);
    }
//
//    vertFile.seekg(0, std::fstream::end);
//    size_t vertBytes = (size_t) vertFile.tellg();
    vertFile.seekg(0, std::fstream::beg);
    std::stringstream vertBuffer;
    vertBuffer << vertFile.rdbuf();

    std::string vertCode = vertBuffer.str();

    vertFile.close();

//    std::cout << vertCode;
    
    const char* tempVert = vertCode.c_str();


    std::string fragFileName = "../shaders/" + name + ".frag";
    std::ifstream fragFile(fragFileName);
    if (fragFile.bad()) {
        std::cout << "FILE " << fragFileName << " NOT FOUND.\n";
        exit(EXIT_FAILURE);
    }

    fragFile.seekg(0, std::fstream::beg);
    std::stringstream fragBuffer;
    fragBuffer << fragFile.rdbuf();

    std::string fragCode = fragBuffer.str();

    fragFile.close();

//    std::cout << fragCode;

    const char* tempFrag = fragCode.c_str();


    Shader shader = glCreateProgram();


    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &tempVert, nullptr);
    glCompileShader(vert);
    GLint vertSuccess;
    glGetShaderiv(vert, GL_COMPILE_STATUS, &vertSuccess);
    if (!vertSuccess) {
        GLint maxLen = 0;
        glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &maxLen);
        char* errorLog = (char*) malloc(sizeof(char) * maxLen);
        glGetShaderInfoLog(vert, maxLen, &maxLen, errorLog);
        printf("VERTEX SHADER ERROR:\n%s\n", errorLog);
        free(errorLog);
    }


    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &tempFrag, nullptr);
    glCompileShader(frag);
    GLint fragSuccess;
    glGetShaderiv(frag, GL_COMPILE_STATUS, &fragSuccess);
    if (!fragSuccess) {
        GLint maxLen = 0;
        glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &maxLen);
        char* errorLog = (char*) malloc(sizeof(char) * maxLen);
        glGetShaderInfoLog(frag, maxLen, &maxLen, errorLog);
        printf("FRAGMENT SHADER ERROR:\n%s\n", errorLog);
        free(errorLog);
    }


    glAttachShader(shader, vert);
    glAttachShader(shader, frag);
    glLinkProgram(shader);

//    free(vertCode);
//    free(fragCode);
    return shader;
}

void shader_bind(Shader shader) {
    glUseProgram(shader);
}

void shader_set_1f(Shader sh, std::string name, float x) {
    glUniform1f(glGetUniformLocation(sh, name.c_str()), x);
}

void shader_set_3f(Shader sh, std::string name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(sh, name.c_str()), x, y, z);
}

void shader_set_1i(Shader sh, std::string name, int x) {
    glUniform1i(glGetUniformLocation(sh, name.c_str()), x);
}

void shader_set_4x4f(Shader sh, std::string name, mat4x4 m) {
    glUniformMatrix4fv(glGetUniformLocation(sh, name.c_str()), 1, GL_FALSE, (const GLfloat*) m);
}