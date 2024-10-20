#include "Object.hpp"

#include <iostream>
#include <exception>

#include <common/Utils.hpp>
#include "Camera.hpp"

namespace world {

    Object::Object(World& parentWorld, const sf::Vector2i& gridPosition, const assets::Tileset& mainTileset, size_t mainTileIndex) 
        : ClickableObject(parentWorld), mainTileset{mainTileset}, mainTileIndex{mainTileIndex}, gridPosition{gridPosition} {
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

    void Object::onHoverEnter() {
        mainSprite.setColor(sf::Color(255, 128, 128, 255));
    }
    
    void Object::onHoverLeave() {
        mainSprite.setColor(sf::Color(255, 255, 255, 255));
    }

    bool Object::isMouseInsideShape(const sf::Vector2f& mouseCameraPosition) {
        const auto box = mainSprite.getGlobalBounds();

        /* Fast */
        if (!box.contains(mouseCameraPosition)) {
            return false;
        }
        
        const sf::IntRect& textureRect = mainSprite.getTextureRect();
        const auto mousePositionInsideTextureRect = static_cast<sf::Vector2i>(box.getPosition() - mouseCameraPosition);
        const auto pixelCoord = textureRect.getPosition() - mousePositionInsideTextureRect;
        
        // Get the pixel data (RGBA) from the texture
        const sf::Image& image = mainTileset.getDeriviedImage();
        sf::Color pixelColor = image.getPixel(pixelCoord.x, pixelCoord.y);

        // std::cout << "Sample pixel: " << pixelCoord << " alpha=" << (int)(pixelColor.a) << std::endl; 
        if (pixelColor.a < 127) {
            return false;
        }

        return true;
    }
    
    std::string Object::toString() const {
        std::stringstream ss;
        ss << "world::Object: " << getGridPosition().x << ", " << getGridPosition().y;
        return ss.str();
    }

    std::string Object::getBrief() const {
        return "Object brief";
    }
}
