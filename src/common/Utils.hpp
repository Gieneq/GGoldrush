#pragma once

#include <SFML/Graphics.hpp>

#include "Properties.hpp"

namespace utils {

    inline sf::Vector2f gridToWordSpace(const sf::Vector2i& gridPosition) {
        return {static_cast<float>(gridPosition.x) * props::BASE_TILESIZE.x, static_cast<float>(gridPosition.y) * props::BASE_TILESIZE.y};
    }
    
    inline sf::Vector2f wordToCameraSpace(const sf::Vector2f& worldPosition) {
        const float isoX = (worldPosition.x / 2.0F - worldPosition.y) - props::BASE_TILESIZE.x / 2.0F;
        const float isoY = (worldPosition.x / 4.0F + worldPosition.y / 2.0F);
        return sf::Vector2f(isoX, isoY);
    }
    
}
