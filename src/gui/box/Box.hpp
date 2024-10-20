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
            invalidate();
        }

        virtual void setVisible(bool visible) override {
            this->visible = visible;
            Drawable::setVisible(visible);
        }

        virtual bool isVisible() const override {
            return visible;
        }

        
        virtual void setTouchable(bool touchable) override {}
        
        virtual bool isTouchable() const override {
            return false;
        }

        virtual void invalidate() override {
            shape.setPosition(getGloblX(), getGlobalY());
        }

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


        void setBackgroundPressed(const sf::Color& backgroundColor) {
            shape.setFillColor(backgroundColor);
        }

    private:
        sf::Vector2f localPosition;

        bool visible;
        
        sf::RectangleShape shape;
    };
}