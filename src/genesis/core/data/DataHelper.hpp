#pragma once

#include "genesis/core/game/chunks/TileGenerator.hpp"

#include <map>
#include <memory>
#include <string>

namespace genesis {

class DataHelper {
private:
    std::map<std::string, std::shared_ptr<TileGenerator>> tileGenerators;

    static inline DataHelper* instance;
public:
    DataHelper();

    std::shared_ptr<TileGenerator> getTileGenerator(const std::string& tile) {
        return tileGenerators.at(tile);
    }
    void registerTileGenerator(const std::string& tileID, std::shared_ptr<TileGenerator> generator);

    static DataHelper* getInstance();
};

}
