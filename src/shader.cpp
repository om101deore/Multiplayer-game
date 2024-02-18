#include "shader.h"
#include <cstdio>
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include <iostream>

Shader::Shader(const char* vertex_path, const char* fragment_path)
{
    unsigned int v_shader = compileShader(vertex_path, GL_VERTEX_SHADER);
    if (v_shader < 0)
        return;

    unsigned int f_shader = compileShader(fragment_path, GL_FRAGMENT_SHADER);
    if (f_shader < 0)
        return;

    // make shader program
    shader_id = glCreateProgram();
    glAttachShader(shader_id, v_shader);
    glAttachShader(shader_id, f_shader);
    glLinkProgram(shader_id);

    int  success;
    char infoLog[255];
    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shader_id, 255, NULL, infoLog);
        std::cout << "FAILED TO LINK PROGRAM\n"
                  << infoLog << "\n";
    }

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
}

Shader::~Shader() { }

int Shader::compileShader(const char* shader_path, GLenum shader_type)
{

    std::cout << "inside Shader::compileShader class" << std::endl;
    // get vertex shader source from file and convert to char*
    FILE* shader_file = fopen(shader_path, "r");

    if (!shader_file) {
        std::cout << "FAILED TO OPEN FILE: " << shader_path << "\n";
        return -1;
    }

    std::string shader_string;

    while (!feof(shader_file)) {
        shader_string += fgetc(shader_file);
    }

    const char* shader_source = shader_string.c_str();

    // vertex shader

    unsigned int shader;
    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Couldn't compile shader"
                  << (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << "\n";
        std::cout << infoLog << "\n";
        return -1;
    }

    return shader;
}

void Shader::useShader() const
{
    glUseProgram(shader_id);
}
