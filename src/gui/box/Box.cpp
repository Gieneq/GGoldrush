#include "Box.hpp"

namespace gui {

    Box::Box() : visible{true} {
        shape.setFillColor(sf::Color(80, 80, 90));
    }
    
    void Box::draw(sf::RenderWindow& target) {
        if (isVisible()) {
            target.draw(shape);
        }
    }

}