#include "FontManger.hpp"
#include <iostream>
#include <exception>
#include <filesystem>


namespace gui {

    FontManager::FontManager() {
        loadFont(latoRegular,   "res/fonts/LatoRegular.ttf");
        loadFont(robotoLight,   "res/fonts/Roboto_Light.ttf");
        loadFont(robotoRegular, "res/fonts/Roboto_Regular.ttf");
        loadFont(robotoMedium,  "res/fonts/Roboto_Medium.ttf");
        loadFont(robotoBold,    "res/fonts/Roboto_Bold.ttf");
    }

    sf::Font& FontManager::getFont(Style style) {
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

        default:
            throw std::invalid_argument("Invalid font style");
        }
    }

    void FontManager::loadFont(sf::Font& font, const std::string& filepath) {
        std::filesystem::path fullPath = std::filesystem::absolute(filepath);
        std::cout << "Attempt to load font from: " << fullPath.string() << std::endl;
        
        if (!font.loadFromFile(filepath)) {
            std::string errorMessage = "Failed to load font from file: " + filepath;
            
            throw std::runtime_error(errorMessage);
        }

        std::cout << "Got font: " << font.getInfo().family << std::endl;
    }
    
} 
