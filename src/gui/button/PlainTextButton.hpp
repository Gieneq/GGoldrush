#pragma once

#include <SFML/Graphics.hpp>

#include <gui/button/PlainButton.hpp>

#include <gui/font/FontManger.hpp>


namespace gui {
    class PlainTextButton : public PlainButton {
    public:
        PlainTextButton(gui::FontManager::Style fontStyle);

        PlainTextButton(gui::FontManager::Style fontStyle, const std::string labelText);

        void draw(sf::RenderWindow& target) override;

        virtual void setParent(Drawable* parent) override {
            PlainButton::setParent(parent);
            centerLabelTextInButton();
        }

        virtual void setX(float x) override {
            PlainButton::setX(x);
            centerLabelTextInButton();
        }
        
        virtual void setY(float y) override {
            PlainButton::setY(y);
            centerLabelTextInButton();
        }

        virtual void setWidth(float width) override {
            PlainButton::setWidth(width);
            centerLabelTextInButton();
        }
        
        virtual void setHeight(float height) override {
            PlainButton::setHeight(height);
            centerLabelTextInButton();
        }
    
    protected:
        virtual void uponHover() override;
        
        virtual void uponPress() override;

        virtual void uponRelease() override;

    private:
        void centerLabelTextInButton();
        sf::Text label;

        sf::Color idleTextColor;
        
        sf::Color pressedTextColor;
    };
}