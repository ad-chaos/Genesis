#include "PhysicsWorld.hpp"
#include "genesis/math/physics/Ray.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "spdlog/spdlog.h"

namespace genesis {

void PhysicsWorld::registerControllers(int scene, const std::vector<std::shared_ptr<PhysicsController>>& controllers) {
    this->stageControllerMap[scene] = controllers;
}

void PhysicsWorld::tick() {
    for (auto& controller : stageControllerMap.at(Renderer::getInstance().getActiveScene())) {
        controller->tick();
    }
}

void PhysicsWorld::clickElement(double x, double y) {
    std::shared_ptr<Entity> touched = Ray::doesIntersect(Ray::normalizeScreenCoords(x, y));
    //for (auto& scene : Renderer::getInstance().getActiveSceneStack()) {
        //for (auto& controller : scene->getEntityControllers()) {
            //if (controller->hasCollision(worldCoords)) {
                //break;
            //}
        //}
    //}

}

}
