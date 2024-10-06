#pragma once

#include <SFML/Graphics.hpp>

#include "Picker.hpp"

namespace assets {
    class Tileset;
}

namespace world {

    class Object : public SelectableObject {
    protected:
    friend class World;
        Object(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, size_t tileIndex);
        virtual ~Object() = default;
        Object(const Object&) = delete;
        Object& operator=(const Object&) = delete;
    
    public:
        virtual void tick() {}

        virtual void draw(sf::RenderWindow& target);

    protected:
        sf::Sprite mainSprite; 
        const assets::Tileset* const mainTileset;
        size_t mainTileIndex;
    };

}