#include "Tile.hpp"

#include "assets/AssetsManager.hpp"
#include "common/Utils.hpp"

#include <iostream>

namespace world {

    Tile::Tile(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, const size_t tileIdx) : tileset{tileset}, tileIdx{tileIdx} {
        const auto worldPosition = utils::gridToWordSpace(gridPosition);
        const auto camPosition = utils::wordToCameraSpace(worldPosition);
        sprite.setPosition(camPosition);
        sprite.setTexture(tileset->getTexture());
        sprite.setTextureRect(tileset->getTileRectByIndex(tileIdx));

            std::cout << "Tile created at grid position: (" << gridPosition.x << ", " << gridPosition.y << ")" << std::endl;
    std::cout << "Corresponding world position: (" << worldPosition.x << ", " << worldPosition.y << ")" << std::endl;
    std::cout << "Corresponding cam position: (" << camPosition.x << ", " << camPosition.y << ")" << std::endl;
    std::cout << "Sprite  position: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")" << std::endl;
    std::cout << "Tile index: " << tileIdx << std::endl;
    std::cout << "Texture rect for tile: (" 
              << sprite.getTextureRect().left << ", " 
              << sprite.getTextureRect().top << ", " 
              << sprite.getTextureRect().width << ", " 
              << sprite.getTextureRect().height << ")" << std::endl;
    }

}