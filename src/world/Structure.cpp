#include "Structure.hpp"

#include <iostream>
#include <exception>

#include "assets/AssetsManager.hpp"
#include <common/Utils.hpp>
#include <world/Camera.hpp>

namespace world {

    Structure::Structure(World& parentWorld, const sf::Vector2i& gridPosition, const assets::Tileset& tileset, size_t tileIndex) 
        : world::Object(parentWorld, gridPosition, tileset, tileIndex) {

        // const auto worldPosition = world::Camera::gridToWorldSpace(gridPosition);
        // const auto cameraPosition = world::Camera::worldToCameraSpace(worldPosition);

        /* Top of tile */
        if ((tileset.getTileSize().x % props::BASE_TILESIZE.x != 0) || (tileset.getTileSize().y % props::BASE_TILESIZE.y != 0)) {
            const std::string errmsg = "Tileset tilesize not equal n * base size: [" 
                + std::to_string(tileset.getTileSize().x) + ", " + std::to_string(tileset.getTileSize().y) + "]";
            std::cerr << errmsg << std::endl;
            throw std::invalid_argument(errmsg);
        }
    }

    void Structure::draw(sf::RenderWindow& target) {
        Object::draw(target);
    }

    std::string Structure::toString() const {
        return "Structure";
    }

    std::string Structure::getBrief() const {
        return "Structure brief";
    }
}