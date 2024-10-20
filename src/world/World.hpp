#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <vector>

#include "Camera.hpp"
#include "Picker.hpp"

#include <common/Properties.hpp>
#include <game/Player.hpp>

namespace world {

    class Tile;
    class Structure;
    class ObjectsBuilder;

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

        game::Player& getPlayer() {
            return player;
        }
        
        void processEvents(const sf::Event& event, const sf::Vector2i& mousePosition);

    private:
        void onClickableObjectEvent(ClickableObject* cobj, Event evt) override;

        void buildTest();

        Camera camera;

        sf::Vector2u size;

        std::vector<Structure*> structures;

        std::vector<Tile*> groundTiles;

        ObjectsBuilder* objectsBuilder;

        Picker picker;

        game::Player player;
    };

}