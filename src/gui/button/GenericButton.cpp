#include "GenericButton.hpp"

#include <iostream>

namespace gui {

    GenericButton::GenericButton() : listener{nullptr}, visible{true}, touchable{true}, pressed{false} {
        uponRelease();
    }
    
    void GenericButton::processEvents(const gui::ClickEvent& event) {
        if (isVisible() && isTouchable()) {

            std::cout << event << std::endl;

            if (isPointInsideGlobally(event.mousePosition.x, event.mousePosition.y)) {
                
                if (event.type == gui::ClickEvent::Type::RELEASED) {
                    pressed = false;
                    uponRelease();

                    /* Is click released inside button */
                    if (listener) {
                        listener->onButtonClicked(this);
                    }
                        
                } 
                else if (event.type == gui::ClickEvent::Type::PRESSED) {
                    pressed = true;
                    uponPress();
                }

            }
            else if (isPressed()) {
                pressed = false;
                uponRelease();
            }

        }
    }

}