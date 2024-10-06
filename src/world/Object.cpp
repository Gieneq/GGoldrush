#include "Object.hpp"

#include <iostream>
#include <exception>

#include "assets/AssetsManager.hpp"
#include <common/Utils.hpp>
#include <world/Camera.hpp>

namespace world {

    Object::Object(const sf::Vector2i& gridPosition, const assets::Tileset* const mainTileset, size_t mainTileIndex) 
        : SelectableObject(), mainTileset{mainTileset}, mainTileIndex{mainTileIndex} {
        const auto worldPosition = world::Camera::gridToWorldSpace(gridPosition);
        const auto cameraPosition = world::Camera::worldToCameraSpace(worldPosition);

        mainSprite.setOrigin({mainTileset->getTileSize().x / 2.0F, 0.0F});
        mainSprite.setPosition(cameraPosition);
        mainSprite.setTexture(mainTileset->getTexture());
        mainSprite.setTextureRect(mainTileset->getTileRectByIndex(mainTileIndex));
    }

    void Object::draw(sf::RenderWindow& target) {
        target.draw(mainSprite);
    }  
}