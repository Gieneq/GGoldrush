#include "Box.hpp"

namespace gui {

    Box::Box() : visible{true} {

    }
    
    void Box::draw(sf::RenderWindow& target) {

        if (isVisible()) {
            target.draw(shape);
        }
    }

}