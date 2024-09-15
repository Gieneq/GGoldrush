#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include <gui/Drawable.hpp>

namespace gui {

    class Container : public Drawable {
    public:
        Container() : Drawable() {}
        
        void add(Drawable* drawable);
        
        virtual void tick() {
            if (isVisible()) {
                for (auto drawable: drawables) {
                    drawable->tick();
                }
            }
        }

        virtual void draw(sf::RenderWindow& target) {
            if (isVisible()) {
                for (auto drawable: drawables) {
                    drawable->draw(target);
                }
            }
        }
        
        virtual void processEvents(const gui::ClickEvent& event) {
            if (isVisible() && isTouchable()) {
                for (auto drawable: drawables) {
                    drawable->processEvents(event);
                }
            }
        }

        virtual void setX(float x) {
            this->x = x;
        }
        
        virtual void setY(float y) {
            this->y = y;
        }

        virtual void setWidth(float width) {
            this->width = width;
        }
        
        virtual void setHeight(float height) {
            this->height = height;
        }
        

        virtual float getX() const {
            return x;
        }
        
        virtual float getY() const {
            return y;
        }

        virtual float getWidth() const {
            return width;
        }
        
        virtual float getHeight() const {
            return height;
        }

        
        virtual void setVisible(bool visible) {
            this->visible = visible;
        }

        virtual bool isVisible() const {
            return visible;
        }

        
        virtual void setTouchable(bool touchable) {
            this->touchable = touchable;
        }
        
        virtual bool isTouchable() const {
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