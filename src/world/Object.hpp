#pragma once

#include <SFML/Graphics.hpp>

#include "assets/AssetsManager.hpp"
#include "Picker.hpp"

namespace world {

    class Object : public ClickableObject {
    protected:
    friend class ObjectsBuilder;
        Object(const sf::Vector2i& gridPosition, const assets::Tileset& tileset, size_t tileIndex);
        virtual ~Object() = default;
        Object(const Object&) = delete;
        Object& operator=(const Object&) = delete;
    
    public:
        virtual void tick() {}

        virtual void draw(sf::RenderWindow& target);

        const sf::Vector2i& getGridPosition() const {
            return gridPosition;
        }

        virtual void onHoverEnter() override;

        virtual void onHoverLeave() override;

        virtual bool isMouseInsideShape(const sf::Vector2f& mouseCameraPosition) override;

        virtual std::string toString() const override;
        
        virtual std::string getBrief() const override;

    protected:
        sf::Sprite mainSprite; 
        const assets::Tileset& mainTileset;
        size_t mainTileIndex;
        sf::Vector2i gridPosition;
    };

}