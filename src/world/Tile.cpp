#include "Tile.hpp"

#include <iostream>
#include <exception>

#include "assets/AssetsManager.hpp"
#include <common/Utils.hpp>
#include <world/Camera.hpp>

namespace world {

        Tile::Tile(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, size_t tileIndexTop, std::optional<size_t> tileIndexWalls) 
            : tileset{tileset}, tileIndexTop{tileIndexTop}, tileIndexWalls{tileIndexWalls} {
            const auto worldPosition = world::Camera::gridToWorldSpace(gridPosition);
            const auto cameraPosition = world::Camera::worldToCameraSpace(worldPosition);

            /* Top of tile */
            if (tileset->getTileSize().x != props::BASE_TILESIZE.x || tileset->getTileSize().y != props::BASE_TILESIZE.y) {
                throw std::invalid_argument("Top tilesize tilesat bad size");
            }

            spriteTop.setOrigin({tileset->getTileSize().x / 2.0F, 0.0F});
            spriteTop.setPosition(cameraPosition);
            spriteTop.setTexture(tileset->getTexture());
            spriteTop.setTextureRect(tileset->getTileRectByIndex(tileIndexTop));

            /* Walls of tile */
            spriteWalls.setOrigin({tileset->getTileSize().x / 2.0F, 0.0F - tileset->getTileSize().y / 2.0F});
            spriteWalls.setPosition(cameraPosition);
            spriteWalls.setTexture(tileset->getTexture());
            if (tileIndexWalls.has_value()) {
                spriteWalls.setTextureRect(tileset->getTileRectByIndex(tileIndexWalls.value()));
            }
        }
}