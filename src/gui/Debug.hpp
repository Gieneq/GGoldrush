#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <common/Utils.hpp>

namespace gui {

    class DebugOverlay {
    public:
        struct Common {
            sf::Vector2f cameraTranslation;
            sf::Vector2f cameraSize;

            sf::Vector2i mouseScreenSpacePosition;
            sf::Vector2f mouseCameraSpacePosition;
            sf::Vector2f mouseWorldSpacePosition;
        };

    private:
        DebugOverlay(sf::Font& font);
        DebugOverlay(const DebugOverlay&) = delete;
        DebugOverlay operator=(const DebugOverlay&) = delete;

    public:
        void clear();

        void draw(sf::RenderWindow& target);

        static DebugOverlay& get();

        template <typename T>
        DebugOverlay& operator<<(const T& data) {
            stringStream << data;
            return *this;
        }

        Common common;

    private:
        sf::Text text;

        std::ostringstream stringStream;
    };

}