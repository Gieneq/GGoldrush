#include "PlainTextButton.hpp"

#include <iostream>

namespace gui {

    PlainTextButton::PlainTextButton(gui::FontManager::Style fontStyle) : PlainButton(), idleTextColor{255, 0, 0}, pressedTextColor{0, 255, 0} {
        label.setFont(gui::FontManager::getInstance().getFont(fontStyle));
        label.setCharacterSize(24);
        label.setColor(idleTextColor);
    }

    PlainTextButton::PlainTextButton(gui::FontManager::Style fontStyle, const std::string labelText) : PlainTextButton(fontStyle) {
        label.setString(labelText);
    }

    void PlainTextButton::draw(sf::RenderWindow& target) {
        PlainButton::draw(target);
        target.draw(label);
    }
        
    void PlainTextButton::centerLabelTextInButton() {
        //  std::cout <<"Here >>>> GlobX: " << getGloblX() << ", Y: " << getGlobalY() << ", Wh: " << getWidth() << ", " << getHeight() << std::endl;
        label.setPosition(
            getGloblX() + (getWidth() - label.getLocalBounds().width) / 2.0F - label.getLocalBounds().left,
            getGlobalY() + (getHeight() - label.getLocalBounds().height) / 2.0F - label.getLocalBounds().top
        );
    }

    void PlainTextButton::uponHover() {
        PlainButton::uponHover();
    }

    void PlainTextButton::uponPress() {
        PlainButton::uponPress();
        label.setColor(pressedTextColor);
    }

    void PlainTextButton::uponRelease() {
        PlainButton::uponRelease();
        label.setColor(idleTextColor);
    }
    
}
