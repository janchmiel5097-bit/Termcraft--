#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>
#include "../thirdparty/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "./global.hpp"
#include "object/entity.hpp"
#include "object/player.hpp"
#include "object/enemy.hpp"

GLFWwindow* StartGLFW();

const vec4 BG_COLOR = vec4(0x191919ff);

void key_callback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/) {
    bool isPressed = (action == GLFW_PRESS || action == GLFW_REPEAT);

    switch (key) {
        // movement ---
        case    GLFW_KEY_W:     Input.upPressed    = isPressed;     break;
        case    GLFW_KEY_S:     Input.downPressed  = isPressed;     break;
        case    GLFW_KEY_A:     Input.leftPressed  = isPressed;     break;
        case    GLFW_KEY_D:     Input.rightPressed = isPressed;     break;

        case    GLFW_KEY_UP:    Input.upPressed    = isPressed;     break;
        case    GLFW_KEY_DOWN:  Input.downPressed  = isPressed;     break;
        case    GLFW_KEY_LEFT:  Input.leftPressed  = isPressed;     break;
        case    GLFW_KEY_RIGHT: Input.rightPressed = isPressed;     break;
        // --- movement

        case    GLFW_KEY_Q:     exit(0);                    break;

        default: break;
    }
}

int main() {
    ENTITIES.push_back(std::make_unique<PlayerEntity>());
    ENTITIES.push_back(std::make_unique<EnemyEntity>());

    // auto* player = dynamic_cast<PlayerEntity*>(entities[0].get());

    GLFWwindow* window = StartGLFW();
    if (!window) return -1;

    glfwSetKeyCallback(window, key_callback);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float lastFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        //update
        {
            float currentFrame = glfwGetTime();
            float dt = currentFrame - lastFrame;
            lastFrame = currentFrame;

            for (auto& entity : ENTITIES) entity->update(dt);
        }

        //render
        {
            glClearColor(BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
            glClear(GL_COLOR_BUFFER_BIT);
            for (auto& entity : ENTITIES) entity->render();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}

GLFWwindow* StartGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW!\n";
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Termcraft but OpenGL ig", NULL, NULL);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window!\n"; // i dunno how but nvm idk
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    // Glad(OS) hehe
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return nullptr;
    }

    return window;
}
