#include "Tile.hpp"

#include <iostream>
#include <exception>

#include "assets/AssetsManager.hpp"
#include <common/Utils.hpp>
#include <world/Camera.hpp>

namespace world {

    Tile::Tile(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, size_t tileIndexTop, std::optional<size_t> tileIndexWalls) 
        : world::Object(gridPosition, tileset, tileIndexTop), tileIndexWalls{tileIndexWalls} {

        const auto worldPosition = world::Camera::gridToWorldSpace(gridPosition);
        const auto cameraPosition = world::Camera::worldToCameraSpace(worldPosition);

        /* Top of tile */
        if (tileset->getTileSize().x != props::BASE_TILESIZE.x || tileset->getTileSize().y != props::BASE_TILESIZE.y) {
            throw std::invalid_argument("Tileset tilesize not equal base size");
        }

        /* Walls of tile */
        spriteWalls.setOrigin({tileset->getTileSize().x / 2.0F, 0.0F - tileset->getTileSize().y / 2.0F});
        spriteWalls.setPosition(cameraPosition);
        spriteWalls.setTexture(tileset->getTexture());
        if (tileIndexWalls.has_value()) {
            spriteWalls.setTextureRect(tileset->getTileRectByIndex(tileIndexWalls.value()));
        }
    }

    void Tile::draw(sf::RenderWindow& target) {
        if (tileIndexWalls.has_value()) {
            target.draw(spriteWalls);
        }
        Object::draw(target);
    }
    
    void Tile::onHover() {
        mainSprite.setColor(sf::Color(255, 200, 200, 255));
    }

    void Tile::onSelect() {
        mainSprite.setColor(sf::Color(255, 128, 128, 255));
    }
    
    void Tile::onNormal() {
        mainSprite.setColor(sf::Color(255, 255, 255, 255));
    }

    bool Tile::isMouseInsideShape(const sf::Vector2f& mouseCameraPosition) {
        const auto box = mainSprite.getGlobalBounds();

        /* Fast */
        if (!box.contains(mouseCameraPosition)) {
            return false;
        }
        // std::cout << box.left << ", " << box.top << ", " << box.width << ", " << box.height << " Mouse: " << mouseCameraPosition << std::endl;

        return true; //TODO
    }

}