#pragma once

#include <iostream>
#include <algorithm>
#include <exception>

#include <SFML/Graphics.hpp>
#include <common/Utils.hpp>
#include <world/World.hpp>

namespace world {

    class ClickableObject {
    friend class Picker;
    public:
 
        ClickableObject(World& parentWorld, bool clickableEnabled = true) 
            : clickable{clickableEnabled}, world{parentWorld} {}

        virtual ~ClickableObject() = default;

        virtual void onReleasedLMB() {}
        
        virtual void onReleasedRMB() {}
        
        virtual void onHoverEnter() {}
        
        virtual void onHoverLeave() {}

        bool clickable;

        virtual std::string toString() const;
        
        virtual std::string getBrief() const;

    protected:
        World& world;

    private:
        bool hovered{false};

        virtual bool isMouseInsideShape(const sf::Vector2f& mouseCameraPosition) {
            return false;
        }
        
    };

    inline std::ostream& operator<<(std::ostream& os, const world::ClickableObject& so) {
        return os << so.toString();
    }
}