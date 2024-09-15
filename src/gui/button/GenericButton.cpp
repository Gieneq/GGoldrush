#include "GenericButton.hpp"

namespace gui {

    GenericButton::GenericButton() : listener{nullptr}, visible{true}, touchable{true} {
        uponRelease();
    }
    
    void GenericButton::processEvents(const gui::ClickEvent& event) {
        if (isVisible() && isTouchable()) {

            if (isPointInside(event.mousePosition.x, event.mousePosition.y)) {

                if (event.type == gui::ClickEvent::Type::RELEASED) {
                    uponRelease();

                    /* Is click released inside button */
                    if (listener) {
                        listener->onButtonClicked(this);
                    }
                        
                } else {
                    uponPress();
                }

            }

        }
    }

}