#pragma once

#include "genesis/math/physics/PhysicsController.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"
#include <map>
#include <memory>
#include <vector>

namespace genesis {

/**
 * Controls a system of entities, which can be considered to be equal to a team.
 */
class EntityController : public Renderable, public PhysicsController {
public:
    virtual ~EntityController() = default;

    void render() override;
    void tick() override = 0;

    void addEntity(const std::shared_ptr<Entity>& entity);
};

} // namespace genesis
