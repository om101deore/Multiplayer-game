#pragma once

#include <glad/glad.h>

class Shader {
public:
    Shader() { }
    Shader(const char* vertex_path, const char* fragment_path);
    ~Shader();
    void useShader() const;

private:
    // shader_id is shader program id
    unsigned int shader_id;

    // returns compiled shader
    int compileShader(const char* shader_path, GLenum shader_type);
};
