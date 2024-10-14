#pragma once

#include <iostream>
#include <utility>

#include <SFML/Graphics.hpp>

#include <world/Structure.hpp>
#include <game/items/Item.hpp>
#include <common/AnimatedSprite.hpp>

//TODO: Only hover with information about produced resource
// On click - extract
//has animated icon with axe or similar
//output storage has refrence to Structure - show icon near building
//player must press ano not leave area to proceed extraction

namespace world {

    class Resourcer : public world::Structure {
    friend class World;
        Resourcer(const sf::Vector2i& gridPosition, const assets::Tileset& tileset, size_t tileIndex, 
            game::ItemType resourceItemType,
            const assets::Tileset& manualExtractTileset, std::pair<size_t, size_t> manualExtractTilesetIndicesRange
        ) : Structure(gridPosition, tileset, tileIndex), resourceItemType{resourceItemType}, manualExtractIcon{{0, 0}, manualExtractTileset, manualExtractTilesetIndicesRange} 
        {
            manualExtractIcon.setVisible(false);
        }

    public:
        virtual void tick() override {
            if (extracting) {
                if (extractingCounter-- < 0) {
                    /* Done */
                    extracting = false;
                    onNormal();
                    //TODO informa pixker by reference or by polling on picker.tick
                }
            }

            manualExtractIcon.tick();
        }

        virtual void draw(sf::RenderWindow& target) override {
            Structure::draw(target);

            manualExtractIcon.draw(target);
        }

        // virtual void onHover() override;

        virtual void onSelect() override {
            extractingCounter = 200;
            extracting = true;
            manualExtractIcon.setVisible(true);
            manualExtractIcon.start();
        }
        
        virtual void onNormal() override {
            if (extracting) {
                /* Interrupted by player */
                std::cout << "Extracting interrupted by player" << std::endl;
            } else {
                /* Finished - give item */
                std::cout << "Player got 1 item with id=" << std::to_string(static_cast<int>(resourceItemType)) << std::endl;
            }

            manualExtractIcon.setVisible(false);
            manualExtractIcon.stop();
        }

        // virtual std::string toString() const override;

        void onManualExtract() {}
        
    private:
        game::ItemType resourceItemType;

        gfx::AnimatedSprite manualExtractIcon;

        int extractingCounter{0};

        bool extracting{false};
    };

}