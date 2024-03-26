#include "game.h"
#include "block.h"
#include "log.h"
#include "shader.h"
#include "socket.h"
#include "tile.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <sys/socket.h>

bool Game::isHost = true;

Game::Game(const char* window_name)
{
    Log(LogLevel::INFO, "IN GAME CONSTRUCTOR");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // game_window
    game_window = glfwCreateWindow(WIDTH, HEIGHT, window_name, NULL, NULL);

    if (!game_window) {
        Log(LogLevel::ERROR, "FAILED TO CREATE WINDOW");
        glfwTerminate();
        return;
    }

    // glad
    glfwMakeContextCurrent(game_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Log(LogLevel::ERROR, "FAILED TO INITIAILISE GLAD");
        return;
    }

    // viewport
    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(game_window, framebufferSizeCallback);

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Game::~Game()
{
    glfwTerminate();
    gSocket->onCleanup();

    Log(LogLevel::INFO, "DONE CLEANING UP");
}

void Game::onLoad()
{
    Log(LogLevel::INFO, "INSIDE Game::onLoad function");

    b        = new Tile();
    b->color = glm::vec3(1.0, 0.644, 0);

    block = new Block();

    s = new Shader("/home/om_d/Codes/break-out/src/shaders/simple_image.vert", "/home/om_d/Codes/break-out/src/shaders/simple_image.frag");

    if (gSocket->isHost) {

        player   = new Player(glm::vec3(5.0f, 2.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        opponent = new Player(glm::vec3(5.0f, 17.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    } else {
        player   = new Player(glm::vec3(5.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        opponent = new Player(glm::vec3(5.0f, 17.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    }
}

void Game::onLoop()
{

    while (!glfwWindowShouldClose(game_window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glm::mat4 mvp;

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 4; j++) {
                b->draw(*s, proj, glm::vec3(0.25f + i, 8.0 + j, 0.0f));
            }
        }

        // draw player
        gSocket->send_message(player->pos);
        player->draw(*s, proj);

        // opponent reads pos into his vector and gets drawn
        gSocket->recv_message(opponent->pos);
        opponent->pos.y = 17.0f;
        opponent->pos.x *= -1;
        opponent->pos.x += 6.0f;
        opponent->draw(*s, proj);

        // testing
        glfwSwapBuffers(game_window);
        glfwPollEvents();

        onInput();
    }
}

void Game::onInput()
{
    if (glfwGetKey(game_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(game_window, true);

    if (glfwGetKey(game_window, GLFW_KEY_D) == GLFW_PRESS) {
        player->pos += glm::vec3(speed * 1.0f, 0.0f, 0.0f);
    }

    if (glfwGetKey(game_window, GLFW_KEY_A) == GLFW_PRESS) {
        player->pos += glm::vec3(speed * -1.0f, 0.0f, 0.0f);
    }
}

// callback functions
void Game::framebufferSizeCallback(GLFWwindow* game_window, int width, int height)
{
    glViewport(0, 0, width, height);
}
