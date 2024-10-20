#pragma once

#include <SFML/Graphics.hpp>
#include "World.hpp"

namespace world {

    class Tile;
    class Resourcer;
    class Extractor;

    class ObjectsBuilder {
        friend class World;

        explicit ObjectsBuilder(World& world) : world{world} {}

        ~ObjectsBuilder() = default;

        Tile* createTileGrass(const sf::Vector2i& gridPosition);

        Tile* createTileDirt(const sf::Vector2i& gridPosition);

        Resourcer* createResourcerForst(const sf::Vector2i& gridPosition);

        Extractor* createExtractorSawmill(const sf::Vector2i& gridPosition);

        World& world;
    };

} 
