#include "Chunk.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"

namespace genesis {

Chunk::Chunk(int chunkX, int chunkY) : chunkX(chunkX), chunkY(chunkY) {

    auto rawObject = std::make_shared<genesis::Model>(genesis::Constants::square, [&](Model* model) {
        model->bindIndexBuffer(genesis::Constants::squareIndices);
        model->createVBO(1, 2, Renderer::getInstance().getTexturePack()->generateFromPosition(0, 12, 64, 64));
    });

    auto& currLevel = chunkMap[0];
    currLevel.resize(Chunk::CHUNK_SIZE);
    for (size_t y = 0; y < CHUNK_SIZE; ++y) {
        auto& vec = currLevel.at(y);
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            auto entity = std::make_shared<genesis::Entity>(
                    rawObject, glm::vec3{chunkX * CHUNK_SIZE + x, chunkY * CHUNK_SIZE + y, -3});
            vec.push_back(entity);
        }
    }
}

void Chunk::render() {
    if (!chunkMap.contains(Renderer::getInstance().getCamera()->getActiveY()))
        return;
    auto& currLevel = chunkMap.at(Renderer::getInstance().getCamera()->getActiveY());

    for (auto& vec : currLevel) {
        for (auto& entity : vec) {
            entity->render();
        }
    }
}

} // namespace genesis
