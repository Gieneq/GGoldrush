#pragma once

#include <iostream>
#include <utility>

#include <SFML/Graphics.hpp>

#include <world/Structure.hpp>
#include <game/items/Item.hpp>
#include <assets/AssetsManager.hpp>
#include <common/AnimatedSprite.hpp>
#include <game/items/Storage.hpp>

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
            World& parentWorld, 
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

        virtual void onReleasedRMB() override;

        virtual std::string toString() const override;
        
        virtual std::string getBrief() const override;
        
    private:
        game::ItemType resourceItemType;

        gfx::AnimatedSprite manualExtractIcon;

        int extractingCounter{0};

        bool extracting{false};

        game::Storage outputStyorage{game::Storage::Quantity::ALL(), 3};

        Type type;
    };

}