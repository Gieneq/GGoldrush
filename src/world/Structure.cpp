#include "Structure.hpp"

#include <iostream>
#include <exception>

#include "assets/AssetsManager.hpp"
#include <common/Utils.hpp>
#include <world/Camera.hpp>

namespace world {

    Structure::Structure(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, size_t tileIndex) 
        : world::Object(gridPosition, tileset, tileIndex) {

        const auto worldPosition = world::Camera::gridToWorldSpace(gridPosition);
        const auto cameraPosition = world::Camera::worldToCameraSpace(worldPosition);

        /* Top of tile */
        if ((tileset->getTileSize().x % props::BASE_TILESIZE.x != 0) || (tileset->getTileSize().y % props::BASE_TILESIZE.y != 0)) {
            throw std::invalid_argument("Tileset tilesize not equal n * base size");
        }
    }

    void Structure::draw(sf::RenderWindow& target) {
        Object::draw(target);
    }
    
    void Structure::onHover() {
        mainSprite.setColor(sf::Color(255, 200, 200, 255));
    }

    void Structure::onSelect() {
        mainSprite.setColor(sf::Color(255, 128, 128, 255));
    }
    
    void Structure::onNormal() {
        mainSprite.setColor(sf::Color(255, 255, 255, 255));
    }

    bool Structure::isMouseInsideShape(const sf::Vector2f& mouseCameraPosition) {
        const auto box = mainSprite.getGlobalBounds();

        /* Fast */
        if (!box.contains(mouseCameraPosition)) {
            return false;
        }
        
        const sf::IntRect& textureRect = mainSprite.getTextureRect();
        const auto mousePositionInsideTextureRect = static_cast<sf::Vector2i>(box.getPosition() - mouseCameraPosition);
        const auto pixelCoord = textureRect.getPosition() - mousePositionInsideTextureRect;
        
        // Get the pixel data (RGBA) from the texture
        const sf::Image& image = mainSprite.getTexture()->copyToImage();
        sf::Color pixelColor = image.getPixel(pixelCoord.x, pixelCoord.y);

        // std::cout << "Sample pixel: " << pixelCoord << " alpha=" << (int)(pixelColor.a) << std::endl; 
        if (pixelColor.a < 127) {
            return false;
        }

        return true;
    }

    std::string Structure::toString() const {
        return "Structure";
    }

}