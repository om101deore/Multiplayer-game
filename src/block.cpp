#include "block.h"
#include "shader.h"
#include <glm/fwd.hpp>

Block::Block()
{
    // inits
    offset = 0.0f;
    model  = glm::mat4(1.0f);

    // ogl stuff
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

Block::~Block()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Block::draw(Shader& shader)
{
    glBindVertexArray(VAO);

    shader.setVec3("col", color);
    shader.useShader();

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
