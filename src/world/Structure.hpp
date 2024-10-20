#pragma once

#include <SFML/Graphics.hpp>

#include <world/Object.hpp>

namespace world {

    class Structure : public world::Object {
    protected:
    friend class ObjectsBuilder;
        Structure(World& parentWorld, const sf::Vector2i& gridPosition, const assets::Tileset& tileset, size_t tileIndex);

    public:
        virtual void tick() override {}

        virtual void draw(sf::RenderWindow& target);

        virtual std::string toString() const override;
        
        virtual std::string getBrief() const override;

    private:
    };

}