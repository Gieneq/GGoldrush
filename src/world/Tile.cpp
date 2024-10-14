#include "Tile.hpp"

#include <iostream>
#include <exception>

#include "assets/AssetsManager.hpp"
#include <common/Utils.hpp>
#include <world/Camera.hpp>

namespace world {

    Tile::Tile(
        Type type, 
        const sf::Vector2i& gridPosition, 
        const assets::Tileset& tileset, 
        size_t tileIndexTop, 
        std::optional<size_t> tileIndexWalls) 
        : type{type}, world::Object(gridPosition, tileset, tileIndexTop), tileIndexWalls{tileIndexWalls} {

        const auto worldPosition = world::Camera::gridToWorldSpace(gridPosition);
        const auto cameraPosition = world::Camera::worldToCameraSpace(worldPosition);

        /* Top of tile */
        if (tileset.getTileSize().x != props::BASE_TILESIZE.x || tileset.getTileSize().y != props::BASE_TILESIZE.y) {
            throw std::invalid_argument("Tileset tilesize not equal base size");
        }

        /* Walls of tile */
        spriteWalls.setOrigin({tileset.getTileSize().x / 2.0F, mainSprite.getOrigin().y - tileset.getTileSize().y / 2.0F});
        spriteWalls.setPosition(cameraPosition);
        spriteWalls.setTexture(tileset.getTexture());
        if (tileIndexWalls.has_value()) {
            spriteWalls.setTextureRect(tileset.getTileRectByIndex(tileIndexWalls.value()));
        }
    }

    void Tile::draw(sf::RenderWindow& target) {
        if (tileIndexWalls.has_value()) {
            target.draw(spriteWalls);
        }
        Object::draw(target);
    }

    std::string Tile::toString() const {
        return "Tile";
    }

    std::string Tile::getBrief() const {
        switch (type)    {
        case Type::GRASS:
            return "Grass tile";

        case Type::DIRT:
            return "Dirt tile";
        
        default:
            return "Unknown tile";
        }
    }
}