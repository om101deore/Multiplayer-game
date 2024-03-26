#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader() { }
    Shader(const char* vertex_path, const char* fragment_path);
    ~Shader();
    void useShader() const;
    void setInt(const char* name, int value) const;
    void setFloat(const char* name, float value) const;
    void setMat4(const char* name, glm::mat4 value) const;
    void setVec3(const char* name, glm::vec3 value) const;
    void setVec2(const char* name, glm::vec2 value) const;

private:
    // shader_id is shader program id
    unsigned int shader_id;

    // returns compiled shader
    int compileShader(const char* shader_path, GLenum shader_type);
};
