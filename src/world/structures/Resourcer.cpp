#include "Resourcer.hpp"

namespace world {
    
    Resourcer::Resourcer(
        Type type, 
        const sf::Vector2i& gridPosition, 
        const assets::Tileset& tileset, 
        size_t tileIndex, 
        game::ItemType resourceItemType,
        gfx::AnimatedSprite&& manualExtractionIcon
    ) : type{type}, 
        Structure(gridPosition, tileset, tileIndex), 
        resourceItemType{resourceItemType}, 
        manualExtractIcon{manualExtractionIcon} 
    {
        manualExtractIcon.setVisible(false);
        manualExtractIcon.setPosition(mainSprite.getPosition());
    }

    void Resourcer::tick() {
        if (extracting) {
            if (extractingCounter-- < 0) {
                /* Done - give item  */
                extracting = false;
                manualExtractIcon.setVisible(false);
                manualExtractIcon.stop();
                onManualExtract();
            }
        }

        manualExtractIcon.tick();
    }

    void Resourcer::draw(sf::RenderWindow& target) {
        Structure::draw(target);

        manualExtractIcon.draw(target);
    }

    void Resourcer::onManualExtract() {
        std::cout << "Player got 1 item with id=" << std::to_string(static_cast<int>(resourceItemType)) << std::endl;
    }

    void Resourcer::onReleasedLMB() {
        Structure::onReleasedLMB();
        if (!extracting) {
            extractingCounter = 200;
            extracting = true;
            manualExtractIcon.setVisible(true);
            manualExtractIcon.start();
        }
    }

    std::string Resourcer::toString() const {
        return "Structure";
    }

    std::string Resourcer::getBrief() const {
        switch (type) {
        case Type::FOREST:
            return "Forest";
        
        case Type::MOUNTSIN:
            return "Mountains";

        default:
            return "Unknown";
        }
    }

}