#include "World.hpp"

#include <iostream>
#include <algorithm>

#include "Tile.hpp"
#include "Structure.hpp"
#include "structures/Resourcer.hpp"

namespace world {

    World::World(const sf::Vector2u& size) : size{size} {
        picker.addListener(this);
        buildTest();
    }

    void World::tick(float dt) {
        camera.tick(dt);
        
        for (const auto& structure: structures) {
            structure->tick();
        }
    }

    void World::draw(sf::RenderWindow& target) {
        int cnt = 0;
        for (const auto& tile: groundTiles) {
            tile->draw(target);
        }

        /* Back to front */
        std::sort(structures.begin(), structures.end(), [](const Structure* s1, const Structure* s2){
            return s2->getGridPosition().y > s1->getGridPosition().y;
        });
        for (const auto& structure: structures) {
            structure->draw(target);
        }
    }

    void World::processEvents(const sf::Event& event, const sf::Vector2i& mousePosition) {
        camera.processEvents(event, mousePosition);

        picker.prepareCheck();

        /* Front to back */
        std::sort(structures.begin(), structures.end(), [](const Structure* s1, const Structure* s2){
            return s1->getGridPosition().y > s2->getGridPosition().y;
        });
        for (auto structure : structures) {
            picker.addSelectable(structure);
        }

        for (auto tile : groundTiles) {
            picker.addSelectable(tile);
        }
        // picker.addSelectable(groundTiles[0]);

        const auto mouseCameraPosition = camera.transformScrenToCameraSpace(mousePosition);
        picker.processEvents(event, mouseCameraPosition);
    }

    Tile* World::createTile(const sf::Vector2i& gridPosition, const assets::Tileset& tileset, const size_t tileIdx) {
        const auto newTile = new Tile(gridPosition, tileset, tileIdx, 225);

        groundTiles.push_back(newTile);

        return newTile;
    }
    
    void World::onSelectableObjectGoSelected(SelectableObject* selObj) {
        Structure* foundStructure = nullptr;
        const auto structureIt = std::find(structures.begin(), structures.end(), selObj);
        if (structureIt != structures.end()) {
            foundStructure = *structureIt;
            std::cout << "Selected Structure: " << *foundStructure << std::endl;
            return;
        }

        Tile* foundTile = nullptr;
        const auto tileIt = std::find(groundTiles.begin(), groundTiles.end(), selObj);
        if (tileIt != groundTiles.end()) {
            foundTile = *tileIt;
            std::cout << "Selected Tile: " << *foundTile << std::endl;
            return;
        }
        
        std::cout << "Selected SelectableObject: " << *selObj << std::endl;
    }

    void World::onSelectableObjectGoNormal(SelectableObject* selObj) {
        Structure* foundStructure = nullptr;
        const auto structureIt = std::find(structures.begin(), structures.end(), selObj);
        if (structureIt != structures.end()) {
            foundStructure = *structureIt;
            std::cout << "Deselected Structure: " << *foundStructure << std::endl;
            return;
        }

        Tile* foundTile = nullptr;
        const auto tileIt = std::find(groundTiles.begin(), groundTiles.end(), selObj);
        if (tileIt != groundTiles.end()) {
            foundTile = *tileIt;
            std::cout << "Deselected Tile: " << *foundTile << std::endl;
            return;
        }
        
        std::cout << "Deelected SelectableObject: " << *selObj << std::endl;
    }
    
    void World::buildTest() {
        const auto& tileset = assets::AssetsManager::getInstane().getTileset(assets::AssetId::COMMON);

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

        //trees
        const auto& structureTileset = assets::AssetsManager::getInstane().getTileset(assets::AssetId::OBJECTS_1X4);
        const auto& meanulExtrTIleset = assets::AssetsManager::getInstane().getTileset(assets::AssetId::EXTRACTIONS);

        const auto newStructure = new Structure({0,0}, structureTileset, 0);
        structures.push_back(newStructure);
        
        const auto newStructure1 = new Resourcer({0,1}, structureTileset, 0, game::ItemType::RAW_WOOD, meanulExtrTIleset, std::make_pair<size_t, size_t>(0, 8));
        structures.push_back(newStructure1);

        //sawmill
        const auto& buildingsTileset = assets::AssetsManager::getInstane().getTileset(assets::AssetId::OBJECTS_2X4);

        const auto newBuilding = new Structure({3,0}, buildingsTileset, 0);
        structures.push_back(newBuilding);
    }

}