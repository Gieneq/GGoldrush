#include "Picker.hpp"
        
#include <iostream>

#include <gui/Debug.hpp>

#include <world/World.hpp>

#include <world/ClickableObject.hpp>

namespace world {
    
    std::string ClickableObject::toString() const {
        return "ClickableObject(clickable=" + std::to_string(clickable) + ")";
    }

    std::string ClickableObject::getBrief() const {
        return "ClickableObject brief";
    }

    ClickableObject* Picker::findClickableObjectByMouseCameraPosition(const sf::Vector2f& mouseCameraPosition) {
        for (auto cobj : batch) {
            if (cobj->isMouseInsideShape(mouseCameraPosition)) {
                return cobj;
            }
        }
        return nullptr;
    }
    
    bool Picker::isClickableObjectInsideBatch(ClickableObject* examinedCobj) {
        for (auto cobj : batch) {
            if (cobj == examinedCobj) {
                return true;
            }
        }
        return false;
    }

    void Picker::processEvents(const sf::Event& event, const sf::Vector2f& mouseCameraPosition) {

        gui::DebugOverlay::get().common.processEventBatchSize = batch.size();
        sf::Clock timer;

        /* Cleared if hoveredLastly somehow disappeared from batch */
        if (hoveredLastly) {
            if (!isClickableObjectInsideBatch(hoveredLastly)) {
                hoveredLastly = nullptr;
                std::cout << "Warning, hoveredLastly got invalid. Fixit" << std::endl;
            }
        }

        /* Hover - separately from click events */
        auto hoveredRecently = findClickableObjectByMouseCameraPosition(mouseCameraPosition);
        if (hoveredRecently != hoveredLastly) {

            /* Any was hover lastly */
            if (hoveredLastly) {
                hoveredLastly->hovered = false;
                hoveredLastly->onHoverLeave();
                notifyAboutEvent(hoveredLastly, ClickableObjectListener::Event::HoverLeave);
            }

            /* Hovered on something */
            if (hoveredRecently) {
                hoveredRecently->hovered = true;
                hoveredRecently->onHoverEnter();
                notifyAboutEvent(hoveredRecently, ClickableObjectListener::Event::HoverEnter);
            }
            hoveredLastly = hoveredRecently;

        }

        const bool clickOccuredLMB{event.type == sf::Event::EventType::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left};
        const bool clickOccuredRMB{event.type == sf::Event::EventType::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Right};

        if (hoveredRecently) {
            if (clickOccuredLMB) {
                hoveredRecently->onReleasedLMB();
                notifyAboutEvent(hoveredRecently, ClickableObjectListener::Event::ReleasedLMB);
            }
            
            if (clickOccuredRMB) {
                hoveredRecently->onReleasedRMB();
                notifyAboutEvent(hoveredRecently, ClickableObjectListener::Event::ReleasedRMB);
            }
        }

        executionTimePeakDetector.updateValue(timer.getElapsedTime().asSeconds());
        gui::DebugOverlay::get().common.processEventProcessTimeSec = executionTimePeakDetector.getMaxValue();
    }

    void Picker::notifyAboutEvent(ClickableObject* selObj, ClickableObjectListener::Event event) {

        for (auto listener : listeners) {
            listener->onClickableObjectEvent(selObj, event);
        }

        switch (event) {
        case ClickableObjectListener::Event::HoverEnter:
            notifyAllOnHoverEnter(selObj);
            break;
        
        case ClickableObjectListener::Event::HoverLeave:
            notifyAllOnHoverLeave(selObj);
            break;
            
        case ClickableObjectListener::Event::ReleasedLMB:
            notifyAllOnReleasedLMB(selObj);
            break;
            
        case ClickableObjectListener::Event::ReleasedRMB:
            notifyAllOnReleasedRMB(selObj);
            break;

        default:
            throw std::invalid_argument("Bad ClickableObjectListener::Event value!");
        }

    }

}