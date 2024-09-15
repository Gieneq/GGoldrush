#pragma once

#include <SFML/Graphics.hpp>

namespace gui {

    class ClickEvent {
    public:
        enum Type {
            PRESSED,
            RELEASED
        };

        ClickEvent(Type type, const sf::Vector2i& mousePosition) 
            : type(type), mousePosition(mousePosition) {}

        Type type;
        sf::Vector2i mousePosition;
    };
}