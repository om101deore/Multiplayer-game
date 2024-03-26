#pragma once

#include "block.h"
#include "player.h"
#include "shader.h"
#include "server.h"
#include "client.h"
#include "socket.h"
#include "tile.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game {
public:
    Game(const char* window_name);
    ~Game();
    void onLoad();
    void onLoop();
    void onInput();

    // callback function
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

private:
    Tile*  b;
    Shader* s;
    Block* block;
    Player* player;
    Player* opponent;

    // multiplayer
    float speed = 0.3f;

    const glm::mat4 proj   = glm::ortho(0.0f, 10.0f, 0.0f, 20.0f);
    const int       WIDTH  = 800;
    const int       HEIGHT = 800;

    GLFWwindow* game_window = NULL;

public:
    Socket* gSocket;

    static bool isHost;
};
