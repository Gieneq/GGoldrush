#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Camera.hpp"
#include "assets/AssetsManager.hpp"

namespace world {

    class Tile;

    class World {
    public:
        World(const sf::Vector2u& size);
        World(const World&) = delete;
        World& operator=(const World&) = delete;

        void tick();

        void draw(sf::RenderWindow& target);

        Camera& getCamera() {
            return camera;
        }

        Tile* createTile(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, const size_t tileIdx);

    private:
        void buildTest();

        Camera camera;

        sf::Vector2u size;

        std::vector<Tile*> allTiles;
    };

}