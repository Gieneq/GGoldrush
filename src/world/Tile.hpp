#pragma once

#include <SFML/Graphics.hpp>

namespace assets {
    class Tileset;
}

namespace world {

    class Tile {
    friend class World;
        Tile(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, const size_t tileIdx);
        ~Tile() = default;
        Tile(const Tile&) = delete;
        Tile& operator=(const Tile&) = delete;

    public:
        virtual void tick() {}

        virtual void draw(sf::RenderWindow& target) {
            target.draw(sprite);
        }

    private:
        sf::Sprite sprite;
        const assets::Tileset* const tileset;
        size_t tileIdx;
    };

}