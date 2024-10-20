#pragma once

#include <iostream>
#include <algorithm>
#include <exception>

#include <SFML/Graphics.hpp>
#include <common/Utils.hpp>

namespace world {

    class ClickableObject;

    class ClickableObjectListener {
    public:
        enum Event {
            ReleasedLMB,
            ReleasedRMB,
            HoverEnter,
            HoverLeave,
        };

        virtual ~ClickableObjectListener() = default;
        virtual void onClickableObjectGotReleasedLMB(ClickableObject* cobj) {}
        virtual void onClickableObjectGotReleasedRMB(ClickableObject* cobj) {}
        virtual void onClickableObjectHoverEnter(ClickableObject* cobj) {}
        virtual void onClickableObjectHoverLeave(ClickableObject* cobj) {}
        virtual void onClickableObjectEvent(ClickableObject* cobj, Event evt) {}
    };
    
    class Picker {
    public:

        Picker() {
            batch.clear();
        }

        void prepareBatch() {
            batch.clear();
        }

        void addClickableObjectToBatch(ClickableObject* cobj) {
            batch.push_back(cobj);
        }

        void addListener(ClickableObjectListener* newListener) {
            if (std::any_of(listeners.begin(), listeners.end(), [newListener](const ClickableObjectListener* listener) {return newListener == listener;})) {
                const std::string err_msg = "Picker listener already added!";
                std::cerr << err_msg << std::endl;
                throw std::invalid_argument(err_msg);
            }
            listeners.push_back(newListener);
        }

        void processEvents(const sf::Event& event, const sf::Vector2f& mouseCameraPosition);

    private:
        ClickableObject* findClickableObjectByMouseCameraPosition(const sf::Vector2f& mouseCameraPosition);
        
        bool isClickableObjectInsideBatch(ClickableObject* cobj);

        std::vector<ClickableObject*> batch;

        ClickableObject* hoveredLastly{nullptr};

        void notifyAboutEvent(ClickableObject* selObj, ClickableObjectListener::Event event);

        void notifyAllOnReleasedLMB(ClickableObject* selObj) {
            for (auto listener : listeners) {
                listener->onClickableObjectGotReleasedLMB(selObj);
            }
        }

        void notifyAllOnReleasedRMB(ClickableObject* selObj) {
            for (auto listener : listeners) {
                listener->onClickableObjectGotReleasedRMB(selObj);
            }
        }

        void notifyAllOnHoverEnter(ClickableObject* selObj) {
            for (auto listener : listeners) {
                listener->onClickableObjectHoverEnter(selObj);
            }
        }

        void notifyAllOnHoverLeave(ClickableObject* selObj) {
            for (auto listener : listeners) {
                listener->onClickableObjectHoverLeave(selObj);
            }
        }

        std::vector<ClickableObjectListener*> listeners;

        utils::PeakDetector executionTimePeakDetector;
    };

}
