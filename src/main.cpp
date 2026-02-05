#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>
#include "../thirdparty/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "./global.hpp"
#include "object/archer.hpp"
#include "object/entity.hpp"
#include "object/giant.hpp"
#include "object/player.hpp"
#include "object/enemy.hpp"

GLFWwindow* StartGLFW();

const vec4 BG_COLOR = vec4(0x191919ff);

inline void restart() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    GLOBAL_PLAYER_TOTAL_HEALTH = GLOBAL_UPGRADE_PLAYER_MAX_HEALTH;

    ENTITIES.clear();
    ENTITIES.push_back(std::make_unique<PlayerEntity>());

    ENTITIES.push_back(std::make_unique<EnemyEntity>());
    ENTITIES.push_back(std::make_unique<EnemyEntity>());
    ENTITIES.push_back(std::make_unique<EnemyEntity>());
    ENTITIES.push_back(std::make_unique<EnemyEntity>());
    ENTITIES.push_back(std::make_unique<EnemyEntity>());
    ENTITIES.push_back(std::make_unique<EnemyEntity>());

    ENTITIES.push_back(std::make_unique<GiantEntity>());
    ENTITIES.push_back(std::make_unique<GiantEntity>());

    ENTITIES.push_back(std::make_unique<ArcherEntity>());
    ENTITIES.push_back(std::make_unique<ArcherEntity>());
}

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

        case    GLFW_KEY_SPACE: Input.dashPressed   = isPressed;    break;
        // --- movement

        case    GLFW_KEY_Q:     exit(0);                    break;
        case    GLFW_KEY_R:     REQUEST_RESTART = true;             break;

        default: break;
    }
}

int main() {
    restart();

    // auto* player = dynamic_cast<PlayerEntity*>(ENTITIES[0].get());

    GLFWwindow* window = StartGLFW();
    if (!window) return -1;

    glfwSetKeyCallback(window, key_callback);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float lastFrame = glfwGetTime();

    while (glfwWindowShouldClose(window) == 0) {
        //update
        {
            float currentFrame = glfwGetTime();
            float dt = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // restarting
            if (REQUEST_RESTART) {
                restart();
                REQUEST_RESTART = false;
                continue; // skip frame
            }

            // update all entities
            for (auto &e : ENTITIES) {
                e->update(dt);
            }

            // remove anything marked for deletion
            ENTITIES.erase(
                std::remove_if(ENTITIES.begin(), ENTITIES.end(),
                [](auto &e) { return e->toDelete; }),
                ENTITIES.end()
            );

            // add newly spawned entities
            ENTITIES.insert(
                ENTITIES.end(),
                std::make_move_iterator(PENDING_ENTITIES.begin()),
                std::make_move_iterator(PENDING_ENTITIES.end())
            );
            PENDING_ENTITIES.clear();

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
