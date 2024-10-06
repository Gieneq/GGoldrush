#include "Tile.hpp"

#include "assets/AssetsManager.hpp"
#include <common/Utils.hpp>
#include <world/Camera.hpp>

#include <iostream>

namespace world {

    Tile::Tile(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, const size_t tileIdx) : tileset{tileset}, tileIdx{tileIdx} {
        const auto worldPosition = world::Camera::gridToWorldSpace(gridPosition);
        const auto cameraPosition = world::Camera::worldToCameraSpace(worldPosition);
        sprite.setOrigin({tileset->getTileSize().x / 2.0F, 0.0F});
        sprite.setPosition(cameraPosition);
        sprite.setTexture(tileset->getTexture());
        sprite.setTextureRect(tileset->getTileRectByIndex(tileIdx));
    }

}