#include "game.h"
#include "block.h"
#include "shader.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

Game::Game()
{
    std::cout << "in game constructor" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // game_window
    game_window = glfwCreateWindow(WIDTH, HEIGHT, "game_window", NULL, NULL);

    if (!game_window) {
        std::cout << "FAILED TO CREATE WINDOW" << std::endl;
        glfwTerminate();
        return;
    }

    // glad
    glfwMakeContextCurrent(game_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "FAILED TO INITIAILISE GLAD" << std::endl;
        return;
    }

    // viewport
    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(game_window, framebufferSizeCallback);
}

Game::~Game()
{
    glfwTerminate();
}

void Game::onLoad()
{
    std::cout<<"in side Game::onLoad()\n";

    b = new Block();
    s = new Shader("/home/om_d/Codes/break-out/src/shaders/simple_image.vert", "/home/om_d/Codes/break-out/src/shaders/simple_image.frag");
}

void Game::onLoop()
{

    while (!glfwWindowShouldClose(game_window)) {
        onInput();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        b->draw(*s);
        glfwSwapBuffers(game_window);
        glfwPollEvents();
    }
}

void Game::onInput()
{
    if (glfwGetKey(game_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(game_window, true);

    if (glfwGetKey(game_window, GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "pressed w\n";
    }
    if (glfwGetKey(game_window, GLFW_KEY_S) == GLFW_PRESS) {
        std::cout << "pressed s\n";
    }
}

// callback functions
void Game::framebufferSizeCallback(GLFWwindow* game_window, int width, int height)
{
    glViewport(0, 0, width, height);
}
