#pragma once

#include <gui/common/events.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <gui/Style.hpp>

namespace gui {

    class Drawable {
    public:
        Drawable() : localPosition{0, 0}, parent{nullptr} {}
        
        ~Drawable() = default;

        virtual void setParent(Drawable* parent) {
            this->parent = parent;
            invalidate(); //will need recalculate
        }
        
        virtual void tick(float dt) {}

        virtual void draw(sf::RenderWindow& target) = 0;
        
        virtual void processEvents(const gui::ClickEvent& event) {}
        
        
        // virtual void onResize(float newWidth, float newHeight) {}


        void setPosition(float x, float y, float width, float height) {
            setX(x);
            setY(y);
            setWidth(width);
            setHeight(height);
        }

        bool isPointInsideGlobally(float gloabl_x, float gloabl_y) {
            return (gloabl_x >= getGlobalX()) && (gloabl_x < (getGlobalX() + getWidth())) 
                && (gloabl_y >= getGlobalY()) && (gloabl_y < (getGlobalY() + getHeight()));
        }

        virtual void setX(float x) {
            localPosition.x = x;
            invalidate();
        }
        
        virtual void setY(float y) {
            localPosition.y = y;
            invalidate();
        }
        
        virtual void setWidth(float width) {
            invalidate();
        }
        
        virtual void setHeight(float height) {
            invalidate();
        }
                
        virtual float getX() const {
            return localPosition.x;
        }
        
        virtual float getY() const {
            return localPosition.y;
        }

        virtual float getWidth() const = 0;
        
        virtual float getHeight() const = 0;

        
        float getGlobalX() const {
            if (parent) {
                return parent->getGlobalX() + getX();
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

        
        virtual void setVisible(bool visible) = 0;

        virtual bool isVisible() const = 0;

        
        virtual void setTouchable(bool touchable) = 0;
        
        virtual bool isTouchable() const = 0;

        virtual void invalidate() {
            valid = false;
        }

        bool hasParent() const {
            return parent != nullptr;
        }

        virtual std::string toString() const {
            std::ostringstream ss;
            ss << "Drawable: "
               << "Position (" << getX() << ", " << getY() << "), "
               << "GlobalPosition (" << getGlobalX() << ", " << getGlobalY() << "), "
               << "Size (" << getWidth() << "x" << getHeight() << "), "
               << "Visible: " << (isVisible() ? "Yes" : "No") << ", "
               << "Touchable: " << (isTouchable() ? "Yes" : "No");
            return ss.str();
        }
        
        virtual void recalculate() {}
        
        virtual void validate() {
            if (!valid) {
                recalculate();
                valid = true;
            }
        }

    protected:
        bool isValid() const {
            return valid;
        }
        
        Drawable* parent;

    private:
        bool valid{false};
        sf::Vector2f localPosition;
    };

    inline std::ostream& operator<<(std::ostream& os, const Drawable& drawable) {
        return os << drawable.toString();
    }
}