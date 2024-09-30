#pragma once

#include <SFML/Graphics.hpp>

namespace world {

    class Camera {
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

    private:
        sf::View view; 
    };

}