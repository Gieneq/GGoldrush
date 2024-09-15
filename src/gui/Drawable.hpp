#pragma once

#include <gui/common/events.hpp>
#include <iostream>
#include <string>
#include <sstream>

namespace gui {

    class Drawable {
    public:
        Drawable() {}
        
        ~Drawable() = default;

        virtual void setParent(Drawable* parent) {
            this->parent = parent;
        }
        
        virtual void tick() {}

        virtual void draw(sf::RenderWindow& target) = 0;
        
        virtual void processEvents(const gui::ClickEvent& event) {};
        

        virtual void setPosition(float x, float y, float width, float height) {
            setX(x);
            setY(y);
            setWidth(width);
            setHeight(height);
        }

        bool isPointInside(float px, float py) {
            return (px >= getX()) && (px < (getX() + getWidth())) && (py >= getY()) && (py < (getY() + getHeight()));
        }

        virtual void setX(float x) = 0;
        
        virtual void setY(float y) = 0;

        virtual void setWidth(float width) = 0;
        
        virtual void setHeight(float height) = 0;
        

        virtual float getX() const = 0;
        
        virtual float getY() const = 0;

        virtual float getWidth() const = 0;
        
        virtual float getHeight() const = 0;

        
        virtual float getGloblX() const {
            if (parent) {
                return parent->getGloblX() + getX();
            }
            return getX();
        }
        
        virtual float getGlobalY() const {
            if (parent) {
                const auto parentValue = parent->getGlobalY();
                return parentValue + getY();
            }
            return getY();
        }

        
        virtual void setVisible(bool visible) = 0;

        virtual bool isVisible() const = 0;

        
        virtual void setTouchable(bool touchable) = 0;
        
        virtual bool isTouchable() const = 0;

        virtual std::string toString() const {
            std::ostringstream ss;
            ss << "Drawable: "
               << "Position (" << getX() << ", " << getY() << "), "
               << "GlobalPosition (" << getGloblX() << ", " << getGlobalY() << "), "
               << "Size (" << getWidth() << "x" << getHeight() << "), "
               << "Visible: " << (isVisible() ? "Yes" : "No") << ", "
               << "Touchable: " << (isTouchable() ? "Yes" : "No");
            return ss.str();
        }
        

    private:
        Drawable* parent{nullptr};
    };

    inline std::ostream& operator<<(std::ostream& os, const Drawable& drawable) {
        return os << drawable.toString();
    }
}