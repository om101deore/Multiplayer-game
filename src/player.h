#pragma once

#include "block.h"
#include "log.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

class Player : public Block {
public:
    Player(glm::vec3 startPos, glm::vec3 col)
    {
        pos   = startPos;
        color = col;
    }
    glm::vec3 pos;

    void draw(Shader& s, const glm::mat4& proj)
    {
        // (1, 1, 0) offset
        //glm::mat4 temp = glm::translate(model, pos + glm::vec3(1.0f, 1.0f, 0.0f));
        glm::mat4 temp = glm::translate(model, pos );
        temp           = glm::scale(temp, glm::vec3(1.0f, 0.5f, 1.0f));

        glm::mat4 mvp = proj * temp;
        s.setMat4("model", mvp);

        Block::draw(s);
    }

private:
};
