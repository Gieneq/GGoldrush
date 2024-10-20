#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include <gui/Drawable.hpp>

namespace gui {

    class Container : public Drawable {
    public:
        Container() : Drawable() {}
        
        void add(Drawable* drawable);
        
        virtual void tick(float dt) override;

        virtual void draw(sf::RenderWindow& target) override;
        
        virtual void processEvents(const gui::ClickEvent& event) override;

        virtual void invalidate() override;

        virtual void setX(float x) override {
            this->x = x;
            Drawable::setX(x);
        }
        
        virtual void setY(float y) override {
            this->y = y;
            Drawable::setY(y);
        }

        virtual void setWidth(float width) override {
            this->width = width;
            Drawable::setWidth(width);
        }
        
        virtual void setHeight(float height) override {
            this->height = height;
            Drawable::setHeight(height);
        }

        virtual float getX() const override {
            return x;
        }
        
        virtual float getY() const override {
            return y;
        }

        virtual float getWidth() const override {
            return width;
        }
        
        virtual float getHeight() const override {
            return height;
        }

        virtual void setVisible(bool visible) override {
            this->visible = visible;
            Drawable::setVisible(visible);
        }

        virtual bool isVisible() const override {
            return visible;
        }

        virtual void setTouchable(bool touchable) override {
            this->touchable = touchable;
        }
        
        virtual bool isTouchable() const override {
            return touchable;
        }

    protected:
        std::vector<gui::Drawable*> drawables;

    private:
        bool visible;

        bool touchable;

        float x;

        float y;

        float width;

        float height;
    };

}