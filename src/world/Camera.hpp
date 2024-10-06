#pragma once

#include <SFML/Graphics.hpp>

#include <common/Properties.hpp>

namespace world {

    class Camera {
        /**
         * 
         * Screen space is in real screen matrix. Strarts from top-left
         * Camera space if after apply transaltion in pixels
         * World space is aligned to diamons, each base diamond is 1x1
         * Grid space is world space but in ints
         * 
         * During rendering tiles are offset by halfwidth to match diamond top
         * 
         */
    friend class World;   
        Camera() {}
        Camera(const Camera&) = delete;
        Camera& operator=(const Camera&) = delete;

    public:
        void sameAs(const sf::View& otherView) {
            view = otherView;
        }

        const sf::View& getView() const {
            return view;
        }

        void lookAt(const sf::Vector2f& target) {
            view.setCenter(target);
        }

        void processEvents(const sf::Event& event, const sf::Vector2i& mousePosition);


        /* Space: Screen <> Camera */
        sf::Vector2f transformScrenToCameraSpace(const sf::Vector2i& pointScreenSpace) {
            return {static_cast<float>(pointScreenSpace.x) - getView().getSize().x / 2.0F + getView().getCenter().x,
                    static_cast<float>(pointScreenSpace.y) - getView().getSize().y / 2.0F + getView().getCenter().y};
        }
        
        sf::Vector2i transformCameraToScreenSpace(const sf::Vector2f& pointCameraSpace) {
            return {static_cast<int>(pointCameraSpace.x + getView().getSize().x / 2.0F - getView().getCenter().x),
                    static_cast<int>(pointCameraSpace.y + getView().getSize().y / 2.0F - getView().getCenter().y)};
        }
        

        /* Space: Camera <> World */
        static inline sf::Vector2f cameraToWorldSpace(const sf::Vector2f& cameraPosition) {
            return {cameraPosition.y / props::BASE_TILESIZE.y + cameraPosition.x / props::BASE_TILESIZE.x,
                    cameraPosition.y / props::BASE_TILESIZE.y - cameraPosition.x / props::BASE_TILESIZE.x};
        }

        static inline sf::Vector2f worldToCameraSpace(const sf::Vector2f& worldPosition) {
            return {(worldPosition.x - worldPosition.y) * props::BASE_TILESIZE.x / 2.0F,
                    (worldPosition.x + worldPosition.y) * props::BASE_TILESIZE.y / 2.0F};
        }


        /* Space: World <> Grid */
        static inline sf::Vector2i worldToGridSpace(const sf::Vector2f& worldPosition) {
            return {static_cast<int>(worldPosition.x), static_cast<int>(worldPosition.y)};
        }

        static inline sf::Vector2f gridToWorldSpace(const sf::Vector2i& gridPosition) {
            return {static_cast<float>(gridPosition.x), static_cast<float>(gridPosition.y)};
        }

    private:
        sf::Vector2f lastPressedCameraCenter;
        sf::Vector2i lastPressedMousePosition;
        sf::Vector2i dragDeltaMousePosition;
        bool dragging {false};

        void tick(float dt);
        sf::View view; 
    };

}