#include "Camera.hpp"



namespace world {

    void Camera::tick(float dt) {
    }

    void Camera::processEvents(const sf::Event& event, const sf::Vector2i& mousePosition) {
        switch (event.type) {
        case sf::Event::EventType::MouseButtonPressed:
            /* code */
            if (event.mouseButton.button == sf::Mouse::Button::Right) {
                lastPressedCameraCenter = view.getCenter();
                lastPressedMousePosition = mousePosition;
                dragDeltaMousePosition = {0,0};
                dragging = true;
            }
            break;
            
        case sf::Event::EventType::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Button::Right) {
                dragging = false;
            }
            break;

        case sf::Event::EventType::MouseMoved:
            if (dragging) {
                dragDeltaMousePosition = mousePosition - lastPressedMousePosition;
                view.setCenter(lastPressedCameraCenter - static_cast<sf::Vector2f>(dragDeltaMousePosition));
            }
            break;
        
        default:
            break;
        }
    }
}