#pragma once

#include <SFML/Graphics.hpp>

#include <gui/Drawable.hpp>

namespace gui {

    class Box : public Drawable {
    public:
        Box();

        void draw(sf::RenderWindow& target) override;
    
        virtual void setParent(Drawable* parent) override {
            Drawable::setParent(parent);
            shape.setPosition(getGloblX(), getGlobalY());
        }

        virtual void setVisible(bool visible) {
            this->visible = visible;
        }

        virtual bool isVisible() const {
            return visible;
        }

        
        virtual void setTouchable(bool touchable) {}
        
        virtual bool isTouchable() const {
            return false;
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


        void setBackgroundPressed(const sf::Color& backgroundColor) {
            shape.setFillColor(backgroundColor);
        }

    private:
        sf::Vector2f localPosition;

        bool visible;
        
        sf::RectangleShape shape;
    };
}