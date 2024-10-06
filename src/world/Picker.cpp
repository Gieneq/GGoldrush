#include "Picker.hpp"
        
#include <iostream>

namespace world {
 
    void Picker::processEvents(const sf::Event& event, const sf::Vector2f& mouseCameraPosition) {
        /* Can select up to one */
        bool anyGotSelected{false};

        //deselect

        for (auto sel : selectablesCache) {
            if (!sel->selectable) {
                continue;
            }

            if (sel->isHovered) {
                if (sel->isMouseInsideShape(mouseCameraPosition)) {
                    if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
                        std::cout << "Select from hover!" << std::endl;
                        sel->onSelect();
                        sel->isSelected = true;
                        anyGotSelected = true;
                    }
                } else {
                    std::cout << "Normal from hover!" << std::endl;
                    sel->onNormal();
                    sel->isHovered = false;
                }

            }

            else if (sel->isSelected) {
                if (!sel->isMouseInsideShape(mouseCameraPosition)) {
                    std::cout << "Normal from select!" << std::endl;
                    sel->onNormal();
                    sel->isHovered = false;
                }
            } 

            else {
                if (sel->isMouseInsideShape(mouseCameraPosition)) {
                    if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
                        std::cout << "Select!" << std::endl;
                        sel->onSelect();
                        sel->isSelected = true;
                        anyGotSelected = true;
                    } else {
                        std::cout << "Hover!" << std::endl;
                        sel->onHover();
                        sel->isHovered = true;
                    }
                }
            }
        }
        
    }

}