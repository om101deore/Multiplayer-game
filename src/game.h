#pragma once

#include "block.h"
#include "shader.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game {
public:
    Game();
    ~Game();
    void onLoad();
    void onLoop();
    void onInput();

    // callback function
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

private:
    Block*  b;
    Shader* s;

    const int WIDTH  = 800;
    const int HEIGHT = 800;

    GLFWwindow* game_window = NULL;
};
