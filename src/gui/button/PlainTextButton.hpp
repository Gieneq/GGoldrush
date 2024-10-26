// #pragma once

// #include <SFML/Graphics.hpp>

// #include <gui/button/PlainButton.hpp>

// #include <gui/font/FontManger.hpp>


// namespace gui {
//     class PlainTextButton : public PlainButton {
//     public:
//         PlainTextButton(gui::FontManager::Style fontStyle);

//         PlainTextButton(gui::FontManager::Style fontStyle, const std::string labelText);

//         void draw(sf::RenderWindow& target) override;

//         virtual void invalidate() override {
//             centerLabelTextInButton();
//             PlainButton::invalidate();
//         }
    
//     protected:
//         virtual void uponHover() override;
        
//         virtual void uponPress() override;

//         virtual void uponRelease() override;

//     private:
//         void centerLabelTextInButton();
//         sf::Text label;

//         sf::Color idleTextColor;
        
//         sf::Color pressedTextColor;
//     };
// }