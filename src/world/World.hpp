#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Camera.hpp"
#include "Picker.hpp"
#include "ObjectsBuilder.hpp"

#include <common/Properties.hpp>
#include <game/Player.hpp>

namespace world {

    class Tile;
    class Structure;

    class World : ClickableObjectListener {
    public:
        World(const sf::Vector2u& size);
        World(const World&) = delete;
        World& operator=(const World&) = delete;

        void tick(float dt);

        void draw(sf::RenderWindow& target);

        Camera& getCamera() {
            return camera;
        }
        
        void processEvents(const sf::Event& event, const sf::Vector2i& mousePosition);

        // Tile* createTile(const sf::Vector2i& gridPosition, const assets::Tileset& tileset, const size_t tileIdx);

    private:
        void onClickableObjectEvent(ClickableObject* cobj, Event evt) override;

        void buildTest();

        Camera camera;

        sf::Vector2u size;

        std::vector<Structure*> structures;

        std::vector<Tile*> groundTiles;

        ObjectsBuilder objectsBuilder{this};

        Picker picker;

        game::Player player;
    };

}