#pragma once

#include <SFML/Graphics.hpp>

#include <gui/Drawable.hpp>

#include <vector>

namespace gui {

    class ButtonClickListener;

    class GenericButton : public Drawable {
    public:
        GenericButton();
        
        virtual void processEvents(const gui::ClickEvent& event);

        void setOnClickListener(ButtonClickListener* listener) {
            this->listener = listener;
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

        bool isPressed() const {
            return pressed;
        }

    protected:
        virtual void uponHover() {}

        virtual void uponPress() {}

        virtual void uponRelease() {}

    private:
        ButtonClickListener* listener;

        bool visible;

        bool touchable;

        bool pressed;
    };


    class ButtonClickListener {
    public:
        ButtonClickListener() {}
        ~ButtonClickListener() = default;

        virtual void onButtonClicked(gui::GenericButton* button) = 0;
    };
}