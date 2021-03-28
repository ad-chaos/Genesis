#include "Renderer.hpp"
#include "GLFW/glfw3.h"
#include "Shader.hpp"
#include <iostream>
#include "genesis/rendering/Texture.hpp"
#include "shaders/DefaultShader.hpp"
#include <chrono>
#include <thread>

namespace genesis {

Renderer::Renderer() {
}

int Renderer::initializeWindow() {
    glewExperimental = true;
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, false);
#if defined __APPLE__ || defined __OSX__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(1);

    this->window = glfwCreateWindow(1024, 576, "Genesis", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW." << std::endl;
        return -1;
    }
    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    return 0;
}

void Renderer::renderBlocking() {
    if (this->window == nullptr) {
        throw std::runtime_error("Window is a nullptr");
    }
    DefaultShader shader;
    auto targetTime = std::chrono::duration<double, std::milli>(8.3);

    auto lastTime = std::chrono::high_resolution_clock::now();
    do {
        auto now = std::chrono::high_resolution_clock::now();
        double delta = (now - lastTime).count();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 0, 1, 1);

        shader.apply();
        camera.applyCamera(shader);
        for (auto& object : objects) {
            object->render(shader);
        }
        shader.stop();

        glfwSwapBuffers(window);
        glfwPollEvents();
        auto end = std::chrono::high_resolution_clock::now();
        lastTime = end;
        auto sleepFor = targetTime - (end - now);
        if (sleepFor > std::chrono::milliseconds(0))
            std::this_thread::sleep_for(sleepFor);
    } while (glfwWindowShouldClose(this->window) == 0);

    glfwTerminate();
}

}
