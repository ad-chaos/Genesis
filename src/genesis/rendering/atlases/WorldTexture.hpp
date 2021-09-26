#pragma once

#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Texture.hpp"

#include <map>

namespace genesis {

enum class WorldTile {
    // Ground {{{
    GRASS, //
    STONE, //
    // }}}
    // Entities {{{
    COLONIST_A,
    // }}}
};

class WorldTexture : public Texture {
private:
    std::map<WorldTile, std::shared_ptr<Entity>> models;

public:
    WorldTexture(const std::string& sourceFile);

    std::shared_ptr<Entity> getEntity(WorldTile type) {
        // map takes care of returning a nullptr if the tile doesn't exist
        // But it shouldn't ever trigger a type that doesn't exist. Fucking bigbrain
        // right there, Olivia :blobthinksmart:
        return models[type];
    }
};

} // namespace genesis
