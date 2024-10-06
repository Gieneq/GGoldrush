#pragma once

#include <optional>

#include <SFML/Graphics.hpp>

namespace assets {
    class Tileset;
}

namespace world {

    class Tile {
    friend class World;
        Tile(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, size_t tileIndexTop, std::optional<size_t> tileIndexWalls = std::nullopt);
        ~Tile() = default;
        Tile(const Tile&) = delete;
        Tile& operator=(const Tile&) = delete;

    public:
        virtual void tick() {}

        virtual void draw(sf::RenderWindow& target) {
            if (tileIndexWalls.has_value()) {
                target.draw(spriteWalls);
            }
            target.draw(spriteTop);
        }

    private:
        sf::Sprite spriteTop;
        sf::Sprite spriteWalls;
        const assets::Tileset* const tileset;
        size_t tileIndexTop;
        std::optional<size_t> tileIndexWalls;
    };

}