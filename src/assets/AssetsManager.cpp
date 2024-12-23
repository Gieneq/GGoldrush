#include "AssetsManager.hpp"
#include <iostream>
#include <exception>
#include <filesystem>

#include <common/Properties.hpp>

namespace assets {

    Tileset::Tileset(const sf::Texture& texture, const sf::Vector2u& tileSize) : texture(texture), tileSize(tileSize), deriviedImage{texture.copyToImage()} {
        if (texture.getSize().x % tileSize.x != 0) {
            const std::string err_msg = "Texture width (" + std::to_string(texture.getSize().x) +
                                        ") is not divisible by tile width (" + std::to_string(tileSize.x) + ")";
            std::cerr << err_msg << std::endl;
            throw std::invalid_argument(err_msg);
        }

        if (texture.getSize().y % tileSize.y != 0) {
            const std::string err_msg = "Texture height (" + std::to_string(texture.getSize().y) +
                                        ") is not divisible by tile height (" + std::to_string(tileSize.y) + ")";
            std::cerr << err_msg << std::endl;
            throw std::invalid_argument(err_msg);
        }

        yOffset = (static_cast<int>(getTileSize().y/props::BASE_TILESIZE.y) - static_cast<int>(getTileSize().x/props::BASE_TILESIZE.x)) 
            * static_cast<int>(props::BASE_TILESIZE.y); 
    }

    sf::IntRect Tileset::getTileRectByIndex(unsigned int tileIndex) const {
        unsigned int tilesPerRow = texture.getSize().x / tileSize.x;

        // Compute the tile's position (row and column) based on the index
        unsigned int tileX = tileIndex % tilesPerRow;  // Column number
        unsigned int tileY = tileIndex / tilesPerRow;  // Row number

        // Return the rectangle for the tile
        return sf::IntRect(tileX * tileSize.x, tileY * tileSize.y, tileSize.x, tileSize.y);
    }

    AssetsManager::AssetsManager() {
        loadTexture(textureCommon,        "res/tilesets/tileset_common.png");
        loadTexture(textureItems,         "res/tilesets/tileset_items.png");
        loadTexture(textureExtractions,   "res/tilesets/tileset_extractions.png");
        loadTexture(textureObjects1x4,    "res/tilesets/tileset_objects_1x4.png");
        loadTexture(textureObjects2x4,    "res/tilesets/tileset_objects_2x4.png");
        loadTexture(textureObjects2x2,    "res/tilesets/tileset_objects_2x2.png");
        loadTexture(textureObjects3x3,    "res/tilesets/tileset_objects_3x3.png");

        tilesetCommon = new Tileset(textureCommon, props::BASE_TILESIZE);
        tilesetItems = new Tileset(textureItems, props::BASE_TILESIZE);
        tilesetExtractions = new Tileset(textureExtractions, {128, 128});
        tilesetObjects1x4 = new Tileset(textureObjects1x4, {1 * props::BASE_TILESIZE.x, 4 * props::BASE_TILESIZE.y});
        tilesetObjects2x4 = new Tileset(textureObjects2x4, {2 * props::BASE_TILESIZE.x, 4 * props::BASE_TILESIZE.y});
        tilesetObjects2x2 = new Tileset(textureObjects2x2, {2 * props::BASE_TILESIZE.x, 2 * props::BASE_TILESIZE.y});
        tilesetObjects3x3 = new Tileset(textureObjects3x3, {3 * props::BASE_TILESIZE.x, 3 * props::BASE_TILESIZE.y});
    }

    const sf::Texture& AssetsManager::getTexture(AssetId id) const {
        switch (id) {
        case AssetId::COMMON:
            return textureCommon;

        case AssetId::ITEMS:
            return textureItems;

        case AssetId::EXTRACTIONS:
            return textureExtractions;

        case AssetId::OBJECTS_1X4:
            return textureObjects1x4;

        case AssetId::OBJECTS_2X4:
            return textureObjects2x4;

        case AssetId::OBJECTS_2X2:
            return textureObjects2x2;

        case AssetId::OBJECTS_3X3:
            return textureObjects3x3;
        
        default:
            throw std::invalid_argument("Invalid texture id");
        }
    }

    const assets::Tileset&AssetsManager::getTileset(AssetId id) const {
        switch (id) {
        case AssetId::COMMON:
            return *tilesetCommon;

        case AssetId::ITEMS:
            return *tilesetItems;

        case AssetId::EXTRACTIONS:
            return *tilesetExtractions;

        case AssetId::OBJECTS_1X4:
            return *tilesetObjects1x4;

        case AssetId::OBJECTS_2X4:
            return *tilesetObjects2x4;

        case AssetId::OBJECTS_2X2:
            return *tilesetObjects2x2;

        case AssetId::OBJECTS_3X3:
            return *tilesetObjects3x3;
        
        default:
            throw std::invalid_argument("Invalid texture id");
        }
    }

    void AssetsManager::loadTexture(sf::Texture& texture, const std::string& filepath) {
        std::filesystem::path fullPath = std::filesystem::absolute(filepath);
        std::cout << "Attempt to load texture from: " << fullPath.string() << std::endl;
        
        if (!texture.loadFromFile(filepath)) {
            std::string errorMessage = "Failed to load texture from file: " + filepath;
            
            throw std::runtime_error(errorMessage);
        }

        std::cout << "Got texture with size: " << texture.getSize().x << ", " << texture.getSize().y << std::endl;
    }
}