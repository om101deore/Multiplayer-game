#pragma once

#include "shader.h"
#include <glad/glad.h>

class Block {
public:
    Block();
    ~Block();
    void draw(Shader& shader);

    int       offset;

    glm::vec3 color;

    glm::mat4 model;

private:
    unsigned int VAO, VBO;

    const float vertices[18] = {
        // clang-format off

        // first triangle
         1.0f,  1.0f, 0.0f,  // top right
         1.0f,  0.0f, 0.0f,  // bottom right
         0.0f,  1.0f, 0.0f,  // top left 
        // second triangle
         1.0f,  0.0f, 0.0f,  // bottom right
         0.0f,  0.0f, 0.0f,  // bottom left
         0.0f,  1.0f, 0.0f   // top left

        // clang-format on
    };
};
