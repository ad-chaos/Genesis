#include "Runner.hpp"

#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/Texture.hpp"

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

namespace genesis {

Runner::Runner() : inputManager(*this), renderer(*this) {
    int result = renderer.initializeWindow();
    if (result != 0) {
        throw std::runtime_error("Initializing the window failed");
    }

    std::vector<GLint> indices = {0, 1, 3, 3, 1, 2};
    auto texture = std::make_shared<genesis::Texture>("images/programmer.png");
    auto rawObject = std::make_shared<genesis::Model>(
            genesis::Constants::square, indices, texture->generateFromPosition(0, 12, 64, 64));
    auto object = std::make_shared<genesis::TexturedModel>(rawObject, texture);
    auto entity = std::make_shared<genesis::Entity>(object, glm::vec3{0, -1, -3});
    renderer.objects.push_back(entity);

    glfwSetWindowUserPointer(renderer.getWindow(), &inputManager);
    glfwSetKeyCallback(renderer.getWindow(), [](GLFWwindow* win, int key, int scanCode, int action, int mods) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onKeyPressed(key, scanCode, action, mods);
    });
    glfwSetMouseButtonCallback(renderer.getWindow(), [](GLFWwindow* win, int button, int action, int mods) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onMousePressed(button, action, mods);
    });
    glfwSetCursorPosCallback(renderer.getWindow(), [](GLFWwindow* win, double x, double y) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onMouseMoved(x, y);
    });

    Runner::INSTANCE = this;
}

void Runner::runGame() {
    this->renderer.render();
    auto targetTime = std::chrono::duration<double, std::milli>(8.3);

    auto lastTime = std::chrono::high_resolution_clock::now();
    do {
        auto now = std::chrono::high_resolution_clock::now();
        delta = (now - lastTime).count();

        // TODO: figure out how to best design a loop that makes TPS
        // and FPS separate (... at least partially)
        // At least to the point where FPS != TPS by loop definition
        // Though might never be a problem. A certain degree of async
        // processing might avoid that being necessesary.
        renderer.tick();
        renderer.render();

        auto end = std::chrono::high_resolution_clock::now();
        lastTime = end;
        auto sleepFor = targetTime - (end - now);
        if (sleepFor > std::chrono::milliseconds(0))
            std::this_thread::sleep_for(sleepFor);
    } while (glfwWindowShouldClose(renderer.getWindow()) == 0);

    glfwTerminate();
}

} // namespace genesis
