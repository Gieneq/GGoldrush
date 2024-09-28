#include "PlainButton.hpp"

#include <iostream>

namespace gui {

    void PlainButton::draw(sf::RenderWindow& target) {
        target.draw(shape);
    }

    void PlainButton::uponHover() {

    }

    void PlainButton::uponPress() {
        shape.setFillColor(pressedColor);
    }

    void PlainButton::uponRelease() {
        shape.setFillColor(idleColor);
    }
}
