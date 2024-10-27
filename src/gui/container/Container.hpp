#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include <gui/Drawable.hpp>
#include <gui/box/Box.hpp>

namespace gui {

    class Container : public Drawable {
    public:
        Container();
        
        void add(Drawable* drawable);
        
        virtual void recalculate() override {
            background.recalculate();
        }

        virtual void tick(float dt) override;

        virtual void draw(sf::RenderWindow& target) override;
        
        virtual void processEvents(const gui::ClickEvent& event) override;

        // virtual void onResize(float newWidth, float newHeight) override;

        virtual void setWidth(float width) override {
            this->width = width;
            Drawable::setWidth(width);
            background.setWidth(width);
        }
        
        virtual void setHeight(float height) override {
            this->height = height;
            Drawable::setHeight(height);
            background.setHeight(height);
        }

        virtual float getWidth() const override {
            return width;
        }
        
        virtual float getHeight() const override {
            return height;
        }

        virtual void setVisible(bool visible) override {
            this->visible = visible;
        }

        virtual bool isVisible() const override {
            return visible;
        }

        void backgroundSetVisible(bool visible) {
            background.setVisible(visible);
        }

        virtual void setTouchable(bool touchable) override {
            this->touchable = touchable;
        }
        
        virtual bool isTouchable() const override {
            return touchable;
        }

        virtual void validate() override;

        virtual void invalidate() override;

    protected:
        std::vector<gui::Drawable*> drawables;

        const gui::Box& getBackground() const {
            return background;
        }

    private:

        gui::Box background;

        bool visible;

        bool touchable;

        float width;

        float height;
    };

}