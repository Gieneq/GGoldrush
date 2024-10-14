#pragma once

#include <SFML/Graphics.hpp>

namespace world {

    class World;
    class Tile;
    class Resourcer;
    class Extractor;

    class ObjectsBuilder {
        friend class World;

        ObjectsBuilder(World const* world) : world{world} {}

        Tile* createTileGrass(const sf::Vector2i& gridPosition);

        Tile* createTileDirt(const sf::Vector2i& gridPosition);

        Resourcer* createResourcerForst(const sf::Vector2i& gridPosition);

        Extractor* createExtractorSawmill(const sf::Vector2i& gridPosition);

        World const* world;
    };

} 
