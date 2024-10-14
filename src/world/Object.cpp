#include "Object.hpp"

#include <iostream>
#include <exception>

#include <common/Utils.hpp>
#include <world/Camera.hpp>

namespace world {

    Object::Object(const sf::Vector2i& gridPosition, const assets::Tileset& mainTileset, size_t mainTileIndex) 
        : SelectableObject(), mainTileset{mainTileset}, mainTileIndex{mainTileIndex}, gridPosition{gridPosition} {
        const auto worldPosition = world::Camera::gridToWorldSpace(gridPosition);
        const auto cameraPosition = world::Camera::worldToCameraSpace(worldPosition);


        mainSprite.setOrigin({mainTileset.getTileSize().x / 2.0F, 0.0F + static_cast<float>(mainTileset.getYOffset())});
        mainSprite.setPosition(cameraPosition);
        mainSprite.setTexture(mainTileset.getTexture());
        mainSprite.setTextureRect(mainTileset.getTileRectByIndex(mainTileIndex));
    }

    void Object::draw(sf::RenderWindow& target) {
        target.draw(mainSprite);
    }  
    
    std::string Object::toString() const {
        std::stringstream ss;
        ss << "world::Object: " << getGridPosition().x << ", " << getGridPosition().y;
        return ss.str();
    }

}
