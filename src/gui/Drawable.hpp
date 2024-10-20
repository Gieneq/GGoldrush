#pragma once

#include <gui/common/events.hpp>
#include <iostream>
#include <string>
#include <sstream>

namespace gui {

    class Drawable {
    public:
        Drawable() {
            invalidate();
        }
        
        ~Drawable() = default;

        virtual void setParent(Drawable* parent) {
            this->parent = parent;
            invalidate();
        }
        
        virtual void tick(float dt) {}

        virtual void draw(sf::RenderWindow& target) = 0;
        
        virtual void processEvents(const gui::ClickEvent& event) {};
        

        void setPosition(float x, float y, float width, float height) {
            setX(x);
            setY(y);
            setWidth(width);
            setHeight(height);
        }

        bool isPointInsideGlobally(float gloabl_x, float gloabl_y) {
            return (gloabl_x >= getGloblX()) && (gloabl_x < (getGloblX() + getWidth())) 
                && (gloabl_y >= getGlobalY()) && (gloabl_y < (getGlobalY() + getHeight()));
        }

        virtual void setX(float x) {
            invalidate();
        }
        
        virtual void setY(float y) {
            invalidate();
        }
        
        virtual void setWidth(float width) {
            invalidate();
        }
        
        virtual void setHeight(float height) {
            invalidate();
        }
                
        virtual float getX() const = 0;
        
        virtual float getY() const = 0;

        virtual float getWidth() const = 0;
        
        virtual float getHeight() const = 0;

        
        float getGloblX() const {
            if (parent) {
                return parent->getGloblX() + getX();
            }
            return getX();
        }
        
        float getGlobalY() const {
            if (parent) {
                const auto parentValue = parent->getGlobalY();
                return parentValue + getY();
            }
            return getY();
        }

        
        virtual void setVisible(bool visible) {
            invalidate();
        }

        virtual bool isVisible() const = 0;

        
        virtual void setTouchable(bool touchable) = 0;
        
        virtual bool isTouchable() const = 0;

        virtual void invalidate() {}

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