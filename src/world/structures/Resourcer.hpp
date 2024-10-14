#pragma once

#include <iostream>
#include <utility>

#include <SFML/Graphics.hpp>

#include <world/Structure.hpp>
#include <game/items/Item.hpp>
#include <assets/AssetsManager.hpp>
#include <common/AnimatedSprite.hpp>

namespace world {

    class Resourcer : public world::Structure {
    public:
    enum Type {
        FOREST,
        MOUNTSIN,
    };

    private:
    friend class ObjectsBuilder;
        Resourcer(
            Type type, 
            const sf::Vector2i& gridPosition, 
            const assets::Tileset& tileset, 
            size_t tileIndex, 
            game::ItemType resourceItemType,
            gfx::AnimatedSprite&& manualExtractionIcon
        );

    public:
        virtual void tick() override;

        virtual void draw(sf::RenderWindow& target) override;

        void onManualExtract();

        virtual void onReleasedLMB() override;

        virtual std::string toString() const override;
        
        virtual std::string getBrief() const override;
        
    private:
        game::ItemType resourceItemType;

        gfx::AnimatedSprite manualExtractIcon;

        int extractingCounter{0};

        bool extracting{false};

        Type type;
    };

}