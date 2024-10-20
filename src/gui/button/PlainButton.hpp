#pragma once

#include <SFML/Graphics.hpp>

#include <gui/button/GenericButton.hpp>


namespace gui {
    class PlainButton : public GenericButton {
    public:
        PlainButton() : GenericButton(), idleColor{100, 100, 100}, pressedColor{200, 200, 200}, localPosition{0, 0} {
            uponRelease();
        }

        virtual void draw(sf::RenderWindow& target) override;
        
        virtual void setX(float x) override {
            localPosition.x = x;
            Drawable::setX(x);
        }
        
        virtual void setY(float y) override {
            localPosition.y = y;
            Drawable::setY(y);
        }

        virtual void setWidth(float width) override {
            auto tmpSize = shape.getSize();
            tmpSize.x = width;
            shape.setSize(tmpSize);
            Drawable::setWidth(width);
        }
        
        virtual void setHeight(float height) override {
            auto tmpSize = shape.getSize();
            tmpSize.y = height;
            shape.setSize(tmpSize);
            Drawable::setHeight(height);
        }

        virtual void invalidate() override {
            shape.setPosition(getGloblX(), getGlobalY());
        }

        virtual float getX() const override {
            return localPosition.x;
        }
        
        virtual float getY() const override {
            return localPosition.y;
        }

        virtual float getWidth() const override {
            return shape.getSize().x;
        }
        
        virtual float getHeight() const override {
            return shape.getSize().y;
        }

        void setColorIdle(const sf::Color& color) {
            idleColor = color;
        }

        void setColorPressed(const sf::Color& color) {
            pressedColor = color;
        }

    protected:
        virtual void uponHover() override;
        
        virtual void uponPress() override;

        virtual void uponRelease() override;

    private:
        sf::Vector2f localPosition;

        sf::RectangleShape shape;

        sf::Color idleColor;
        
        sf::Color pressedColor;
    };
}