#pragma once

#include <SFML/Graphics.hpp>

#include <gui/button/GenericButton.hpp>


namespace gui {
    class PlainButton : public GenericButton {
    public:
        PlainButton() : GenericButton(), idleColor{100, 100, 100}, pressedColor{200, 200, 200}, localPosition{0, 0} {
            uponRelease();
        }

        void draw(sf::RenderWindow& target) override;
    
        virtual void setParent(Drawable* parent) override {
            Drawable::setParent(parent);
            shape.setPosition(getGloblX(), getGlobalY());
        }
        
        virtual void setX(float x) {
            localPosition.x = x;
            shape.setPosition(getGloblX(), getGlobalY());
        }
        
        virtual void setY(float y) {
            localPosition.y = y;
            shape.setPosition(getGloblX(), getGlobalY());
        }

        virtual void setWidth(float width) {
            auto tmpWidth = shape.getSize();
            tmpWidth.x = width;
            shape.setSize(tmpWidth);
        }
        
        virtual void setHeight(float height) {
            auto tmpWidth = shape.getSize();
            tmpWidth.y = height;
            shape.setSize(tmpWidth);
        }
        

        virtual float getX() const {
            return localPosition.x;
        }
        
        virtual float getY() const {
            return localPosition.y;
        }

        virtual float getWidth() const {
            return shape.getSize().x;
        }
        
        virtual float getHeight() const {
            return shape.getSize().y;
        }

        void setColorIdle(const sf::Color& color) {
            idleColor = color;
        }

        void setColorPressed(const sf::Color& color) {
            pressedColor = color;
        }

    private:
        void uponPress() override;

        void uponRelease() override;

        sf::Vector2f localPosition;

        sf::RectangleShape shape;

        sf::Color idleColor;
        
        sf::Color pressedColor;
    };
}