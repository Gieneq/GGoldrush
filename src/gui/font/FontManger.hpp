#pragma once

#include <SFML/Graphics.hpp>

namespace gui {

    class FontManager {
        
        FontManager();

    public:
        enum Style {
            LATO_REGULAR,
            ROBOTO_LIGHT,
            ROBOTO_REGULAR,
            ROBOTO_MEDIUM,
            ROBOTO_BOLD
        };

        FontManager(const FontManager&) = delete;
        FontManager& operator=(const FontManager&) = delete;

        sf::Font& getFont(Style style) {
            switch (style) {
            case LATO_REGULAR:
                return latoRegular;

            case ROBOTO_LIGHT:
                return robotoLight;

            case ROBOTO_REGULAR:
                return robotoRegular;

            case ROBOTO_MEDIUM:
                return robotoMedium;

            case ROBOTO_BOLD:
                return robotoBold;
            }
        }

        static FontManager& getInstance() {
            static FontManager instance;
            return instance;
        }

    private:
        void loadFont(sf::Font& font, const std::string& filepath);

        sf::Font latoRegular;

        sf::Font robotoLight;

        sf::Font robotoRegular;
        
        sf::Font robotoMedium;

        sf::Font robotoBold;
    };

}

