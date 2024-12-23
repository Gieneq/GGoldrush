#include "World.hpp"

#include <iostream>
#include <algorithm>

#include "Tile.hpp"
#include "Structure.hpp"
#include "structures/Resourcer.hpp"

#include "ObjectsBuilder.hpp"

namespace world {

    World::World(const sf::Vector2u& size) : size{size}, objectsBuilder{new ObjectsBuilder{*this}} {
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

        picker.prepareBatch();

        /* Front to back */
        std::sort(structures.begin(), structures.end(), [](const Structure* s1, const Structure* s2){
            return s1->getGridPosition().y > s2->getGridPosition().y;
        });
        for (auto structure : structures) {
            picker.addClickableObjectToBatch(structure);
        }

        for (auto tile : groundTiles) {
            picker.addClickableObjectToBatch(tile);
        }

        const auto mouseCameraPosition = camera.transformScrenToCameraSpace(mousePosition);
        picker.processEvents(event, mouseCameraPosition);
    }

    void World::onClickableObjectEvent(ClickableObject* cobj, Event evt) {
        switch (evt) {
        case ClickableObjectListener::Event::ReleasedLMB :
            std::cout << "World::onClickableObjectEvent=ReleasedLMB " << cobj->getBrief() << std::endl;
            break;
            
        case ClickableObjectListener::Event::ReleasedRMB :
            std::cout << "World::onClickableObjectEvent=ReleasedRMB " << cobj->getBrief() << std::endl;
            break;
            
        case ClickableObjectListener::Event::HoverEnter :
            std::cout << "World::onClickableObjectEvent=HoverEnter " << cobj->getBrief() << std::endl;
            break;
            
        case ClickableObjectListener::Event::HoverLeave :
            std::cout << "World::onClickableObjectEvent=HoverLeave " << cobj->getBrief() << std::endl;
            break;
        
        default:
            break;
        }
    }
    
    void World::buildTest() {
        const auto& tileset = assets::AssetsManager::getInstane().getTileset(assets::AssetId::COMMON);

        for (int iy = 0; iy < size.y; iy++) {
            for (int ix = 0; ix < size.x; ix++) {

                const auto newTile = iy < 4 ? objectsBuilder->createTileGrass({ix, iy}) : objectsBuilder->createTileDirt({ix, iy});
                groundTiles.push_back(newTile);

            }
        }

        const auto forest1 = objectsBuilder->createResourcerForst({0, 0});
        structures.push_back(forest1);
        const auto forest2 = objectsBuilder->createResourcerForst({1, 0});
        structures.push_back(forest2);
        const auto forest3 = objectsBuilder->createResourcerForst({0, 1});
        structures.push_back(forest3);
        const auto forest4 = objectsBuilder->createResourcerForst({0, 2});
        structures.push_back(forest4);
        
        const auto sawmill1 = objectsBuilder->createExtractorSawmill({3, 0});
        // structures.push_back(sawmill1);
    }

}