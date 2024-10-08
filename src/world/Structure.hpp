#pragma once

#include <SFML/Graphics.hpp>

#include <world/Object.hpp>

namespace assets {
    class Tileset;
}

namespace world {

    class Structure : public world::Object {
    friend class World;
        Structure(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, size_t tileIndex);

    public:
        virtual void tick() override {}

        virtual void draw(sf::RenderWindow& target);

        virtual void onHover() override;

        virtual void onSelect() override;
        
        virtual void onNormal() override;

        virtual bool isMouseInsideShape(const sf::Vector2f& mouseCameraPosition) override;

        virtual std::string toString() const override;
        
    private:
    };

}