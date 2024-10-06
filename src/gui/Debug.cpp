#include "Debug.hpp"

#include <gui/font/FontManger.hpp>

namespace gui {

    DebugOverlay::DebugOverlay(sf::Font& font) {
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Green);
    }

    DebugOverlay& DebugOverlay::get() {
        static DebugOverlay instance(FontManager::getInstance().getFont(gui::FontManager::Style::ROBOTO_BOLD));
        return instance;
    }

    void DebugOverlay::clear() {
        stringStream.str("");
        stringStream.clear();
    }

    void DebugOverlay::draw(sf::RenderWindow& target) {
        /* Common */
        *this << "Camera: center=" << common.cameraTranslation << "size=" << common.cameraSize << "\n";
        *this << "Mouse: screen=" << common.mouseScreenSpacePosition <<  ", camera=" << common.mouseCameraSpacePosition 
            << ", world=" << common.mouseWorldSpacePosition << "\n";

        /* Instance */
        text.setString(stringStream.str());
        target.draw(text);
    }

}