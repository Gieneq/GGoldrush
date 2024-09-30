#include "World.hpp"

#include <iostream>

#include "Tile.hpp"

namespace world {

    World::World(const sf::Vector2u& size) : size{size} {
        buildTest();
    }

    void World::tick() {

    }

    void World::draw(sf::RenderWindow& target) {
        int cnt = 0;
        for (const auto& tile: allTiles) {
            tile->draw(target);
            // std::cout << "Tile " << cnt++ << ", " << tile->tileIdx 
            //     << "[" << tile->sprite.getGlobalBounds().left << ", " << tile->sprite.getGlobalBounds().top << "; " 
            //     << tile->sprite.getGlobalBounds().width << ", " << tile->sprite.getGlobalBounds().height << "]" << std::endl;
        }
    }

    Tile* World::createTile(const sf::Vector2i& gridPosition, const assets::Tileset* const tileset, const size_t tileIdx) {
        const auto newTile = new Tile(gridPosition, tileset, tileIdx);
        // newTile->

        allTiles.push_back(newTile);

        return newTile;
    }
    
    void World::buildTest() {
        const auto tileset = assets::AssetsManager::getInstane().getTileset(assets::AssetId::COMMON);

        int coloridx=0;
        for (int iy = 0; iy < size.y; iy++) {
            for (int ix = 0; ix< size.x; ix++) {
                
                const auto newTile = createTile(
                    {ix, iy},
                    tileset,
                    static_cast<size_t>(coloridx % 4)
                );
                ++coloridx;

            }
        }
    }

}