#pragma once

#include <optional>

#include <SFML/Graphics.hpp>

#include <world/Object.hpp>

namespace assets {
    class Tileset;
}

namespace world {

    class Tile : public world::Object {
    public:
        enum Type {
            GRASS,
            DIRT,
        };

    private:
    friend class ObjectsBuilder;
        Tile(
            Type type, 
            const sf::Vector2i& gridPosition, 
            const assets::Tileset& tileset, 
            size_t tileIndexTop, 
            std::optional<size_t> tileIndexWalls = std::nullopt);

    public:
        virtual void tick() override {}

        virtual void draw(sf::RenderWindow& target);

        virtual std::string toString() const override;

        virtual std::string getBrief() const override;

    private:
        Type type;
        sf::Sprite spriteWalls;
        std::optional<size_t> tileIndexWalls;
    };

}