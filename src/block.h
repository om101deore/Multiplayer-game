#pragma once

#include "shader.h"
#include <glad/glad.h>

class Block {
public:
    Block();
    ~Block();
    void draw(Shader& shader);

private:
    unsigned int VAO, VBO;

    const float vertices[9] = {
        // clang-format off
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
        // clang-format on
    };
};
