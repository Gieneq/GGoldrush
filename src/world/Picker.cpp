#include "Picker.hpp"
        
#include <iostream>

namespace world {
 
    SelectableObject* Picker::findSelectableObjectByMouseCameraPosition(const sf::Vector2f& mouseCameraPosition) {
        for (auto sel : selectablesCache) {
            if (sel->isMouseInsideShape(mouseCameraPosition)) {
                return sel;
            }
        }
        return nullptr;
    }
    
    bool Picker::isSelectableObjectInsideBatch(SelectableObject* selectableObject) {
        for (auto sel : selectablesCache) {
            if (sel == selectableObject) {
                return true;
            }
        }
        return false;
    }

    void Picker::processEvents(const sf::Event& event, const sf::Vector2f& mouseCameraPosition) {

        /* Deselect if already selected disappeared from batch */
        if (selectedRecently) {
            if (!isSelectableObjectInsideBatch(selectedRecently)) {
                selectedRecently = nullptr;
                std::cout << "Warning, selectedRecently got invalid. Fixit" << std::endl;
            }
        }
        
        const bool clickOccured{event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left};
        // bool clickHitAny{false};

        //deselect with escape

        if (clickOccured) {
            auto nextSelected = findSelectableObjectByMouseCameraPosition(mouseCameraPosition);
            if (!nextSelected && selectedRecently) {
                /* Deselect */
                selectedRecently->isSelected = false;
                selectedRecently->onNormal();
                selectedRecently = nullptr;
            }
            else if (selectedRecently != nextSelected) {
                if (selectedRecently) {
                    /* Deselect */
                    selectedRecently->isSelected = false;
                    selectedRecently->onNormal();
                    selectedRecently = nullptr;
                }

                /* Select next */
                nextSelected->isSelected = true;
                nextSelected->onSelect();
                selectedRecently = nextSelected;
            }
        }
        
    }

}