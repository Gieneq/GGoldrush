#include "ObjectsBuilder.hpp"

#include <utility>

#include <world/Object.hpp>
#include <world/Tile.hpp>
#include <world/Structure.hpp>

#include <world/structures/Resourcer.hpp>
#include <world/structures/Extractor.hpp>

#include <assets/AssetsManager.hpp>
#include <common/AnimatedSprite.hpp>

namespace world {

    Tile* ObjectsBuilder::createTileGrass(const sf::Vector2i& gridPosition) {
        const auto& tileset = assets::AssetsManager::getInstane().getTileset(assets::AssetId::COMMON);
        const size_t topTileIndex = 0;
        const size_t bordersIndex = 225;
        return new Tile(
            world,
            Tile::Type::GRASS,
            gridPosition,
            tileset,
            topTileIndex,
            bordersIndex);
    }

    Tile* ObjectsBuilder::createTileDirt(const sf::Vector2i& gridPosition) {
        const auto& tileset = assets::AssetsManager::getInstane().getTileset(assets::AssetId::COMMON);
        const size_t topTileIndex = 2;
        const size_t bordersIndex = 225;
        return new Tile(
            world,
            Tile::Type::DIRT,
            gridPosition,
            tileset,
            topTileIndex,
            bordersIndex);
    }

    Resourcer* ObjectsBuilder::createResourcerForst(const sf::Vector2i& gridPosition) {
        const auto& tileset = assets::AssetsManager::getInstane().getTileset(assets::AssetId::OBJECTS_1X4);
        const auto& tilesetExtractionIcon = assets::AssetsManager::getInstane().getTileset(assets::AssetId::EXTRACTIONS);
        return new Resourcer(
            world,
            Resourcer::Type::FOREST, 
            gridPosition, 
            tileset, 
            0, 
            game::ItemType::RAW_WOOD, 
            gfx::AnimatedSprite{tilesetExtractionIcon, std::make_pair<size_t, size_t>(0, 8)});
    }


    Extractor* ObjectsBuilder::createExtractorSawmill(const sf::Vector2i& gridPosition) {
        const auto& tileset = assets::AssetsManager::getInstane().getTileset(assets::AssetId::OBJECTS_2X4);
        const auto& tilesetExtractionIcon = assets::AssetsManager::getInstane().getTileset(assets::AssetId::EXTRACTIONS);
        return nullptr; //TODO
        // return new Resourcer(
        //     Extractor::Type::SAWMILL, 
        //     gridPosition, 
        //     tileset, 
        //     0, 
        //     game::ItemType::RAW_WOOD, 
        //     gfx::AnimatedSprite{tilesetExtractionIcon, std::make_pair<size_t, size_t>(0, 8)});
    }
}
