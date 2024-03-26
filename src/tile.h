#pragma once

#include "block.h"
#include <glm/ext/matrix_transform.hpp>

class Tile : public Block {
public:
    void draw(Shader& s, const glm::mat4 proj, glm::vec3 pos)
    {
        glm::mat4 temp = glm::translate(model, pos);
        temp           = glm::scale(temp, glm::vec3(0.5f, 0.5f, 1.0f));
        glm::mat4 mvp  = proj * temp;
        s.setMat4("model", mvp);

        Block::draw(s);
    }
};
