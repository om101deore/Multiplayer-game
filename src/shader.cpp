#include "shader.h"
#include "log.h"

#include <glm/gtc/type_ptr.hpp>
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

        std::string logMsg;
        logMsg += "FAILED TO LINK PROGRAM\n";
        logMsg += infoLog;
        logMsg += "\n";
        Log(LogLevel::ERROR, logMsg.c_str());
    }

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
}

Shader::~Shader() { }

int Shader::compileShader(const char* shader_path, GLenum shader_type)
{

    Log(LogLevel::INFO, "inside Shader::compileShader class");

    // get vertex shader source from file and convert to char*
    FILE* shader_file = fopen(shader_path, "r");

    if (!shader_file) {
        std::string logMsg;
        logMsg += "FAILED TO OPEN FILE: ";
        logMsg += shader_path;
        logMsg += "\n";
        Log(LogLevel::ERROR, logMsg.c_str());

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
        std::string logMsg;

        logMsg += "Couldn't compile shader";
        logMsg += (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment");
        logMsg += "\n";
        logMsg += infoLog;
        logMsg += "\n";

        Log(LogLevel::ERROR, logMsg.c_str());

        return -1;
    }
    return shader;
}

void Shader::useShader() const
{
    glUseProgram(shader_id);
}

void Shader::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(shader_id, name), value);
}

void Shader::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(shader_id, name), value);
}

void Shader::setMat4(const char* name, glm::mat4 mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shader_id, name), 1, GL_FALSE,
        glm::value_ptr(mat));
}

void Shader::setVec3(const char* name, glm::vec3 vec) const
{
    glUniform3fv(glGetUniformLocation(shader_id, name), 1, glm::value_ptr(vec));
}

void Shader::setVec2(const char* name, glm::vec2 vec) const
{
    glUniform2fv(glGetUniformLocation(shader_id, name), 1, glm::value_ptr(vec));
}
