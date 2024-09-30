#pragma once

#include <SFML/Graphics.hpp>


namespace assets {

    /**
     * 
     */
    enum AssetId {
        COMMON,
        OBJECTS_2X2,
        OBJECTS_3X3,
    };


    /**
     * 
     */
    class Tileset {
        Tileset(const sf::Texture& texture, const sf::Vector2u& tileSize);
        Tileset(const Tileset&) = delete;
        Tileset& operator=(const Tileset&) = delete;

    public:
        const sf::Texture& getTexture() const {
            return texture;
        }

        const sf::Vector2u& getTileSize() const {
            return tileSize;
        }

        sf::IntRect getTileRectByIndex(unsigned int tileIndex) const;

    private:
        const sf::Texture& texture;
        const sf::Vector2u tileSize;

        friend class AssetsManager;
    };


    /**
     * 
     */
    class AssetsManager {
        AssetsManager();

    public:

        AssetsManager(const AssetsManager&) = delete;
        AssetsManager& operator=(const AssetsManager&) = delete;

        const sf::Texture& getTexture(AssetId id) const;

        const assets::Tileset* const getTileset(AssetId id) const;

        static AssetsManager& getInstane() {
            static AssetsManager instance;
            return instance;
        }

    private:
        void loadTexture(sf::Texture& texture, const std::string& filepath);

        sf::Texture textureCommon;
        Tileset* tilesetCommon;
        
        sf::Texture textureObjects2x2;
        Tileset* tilesetObjects2x2;

        sf::Texture textureObjects3x3;
        Tileset* tilesetObjects3x3;
    };
    
}