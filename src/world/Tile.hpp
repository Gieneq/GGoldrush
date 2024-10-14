#pragma once

#include <optional>

#include <SFML/Graphics.hpp>

#include <world/Object.hpp>

namespace assets {
    class Tileset;
}

namespace world {

    class Tile : public world::Object {
    friend class World;
        Tile(const sf::Vector2i& gridPosition, const assets::Tileset& tileset, size_t tileIndexTop, std::optional<size_t> tileIndexWalls = std::nullopt);

    public:
        virtual void tick() override {}

        virtual void draw(sf::RenderWindow& target);

        virtual void onHover() override;

        virtual void onSelect() override;
        
        virtual void onNormal() override;

        virtual bool isMouseInsideShape(const sf::Vector2f& mouseCameraPosition) override;

        virtual std::string toString() const override;

    private:
        sf::Sprite spriteWalls;
        std::optional<size_t> tileIndexWalls;
    };

}