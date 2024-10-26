#pragma once

#include <SFML/Graphics.hpp>

#include <gui/Drawable.hpp>

namespace gui {

    class Box : public Drawable {
    public:
        Box() : Drawable(), visible{true} {
            shape.setFillColor(style::DEFAULT_BG_COLOR);
            shape.setSize({20,10});
        }
        
        virtual void recalculate() override {
            shape.setPosition(getGlobalX(), getGlobalY());
        }

        void draw(sf::RenderWindow& target) {
            if (isVisible()) {
                target.draw(shape);
            }
        }
    
        virtual void setParent(Drawable* parent) override {
            Drawable::setParent(parent);
        }

        virtual void setVisible(bool visible) override {
            this->visible = visible;
        }

        virtual bool isVisible() const override {
            return visible;
        }

        
        virtual void setTouchable(bool touchable) override {}
        
        virtual bool isTouchable() const override {
            return false;
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

        virtual float getWidth() const override {
            return shape.getSize().x;
        }
        
        virtual float getHeight() const override {
            return shape.getSize().y;
        }


        void setBackgroundPressed(const sf::Color& backgroundColor) {
            shape.setFillColor(backgroundColor);
        }

    protected:
        sf::RectangleShape& getShape() {
            return shape;
        }

    private:
        bool visible;
        
        sf::RectangleShape shape;
    };
}