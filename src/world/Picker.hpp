#pragma once

#include <iostream>
#include <algorithm>
#include <exception>

#include <SFML/Graphics.hpp>


namespace world {

    class SelectableObject {
    friend class Picker;
    public:
        SelectableObject(bool selectableEnabled = true) : selectable{selectableEnabled} {}
        virtual ~SelectableObject() = default;

        virtual void onHover() {}

        virtual void onSelect() {}
        
        virtual void onNormal() {}

        bool selectable;

        virtual std::string toString() const;

    private:
        bool isHovered{false};
        bool isSelected{false};

        virtual bool isMouseInsideShape(const sf::Vector2f& mouseCameraPosition) {
            return false;
        }
        
    };

    inline std::ostream& operator<<(std::ostream& os, const world::SelectableObject& so) {
        return os << so.toString();
    }

    class SelectableObjectListener {
    public:
        virtual void onSelectableObjectGoSelected(SelectableObject* selObj) {}
        virtual void onSelectableObjectGoNormal(SelectableObject* selObj) {}
    };
    
    class Picker {
    public:

        Picker() {
            selectablesCache.clear();
        }

        void prepareCheck() {
            selectablesCache.clear();
        }

        void addSelectable(SelectableObject* sel) {
            selectablesCache.push_back(sel);
        }

        void addListener(SelectableObjectListener* newListener) {
            if (std::any_of(listeners.begin(), listeners.end(), [newListener](const SelectableObjectListener* listener) {return newListener == listener;})) {
                const std::string err_msg = "Picker listener already added!";
                std::cerr << err_msg << std::endl;
                throw std::invalid_argument(err_msg);
            }
            listeners.push_back(newListener);
        }

        void processEvents(const sf::Event& event, const sf::Vector2f& mouseCameraPosition);

    private:
        SelectableObject* findSelectableObjectByMouseCameraPosition(const sf::Vector2f& mouseCameraPosition);
        
        bool isSelectableObjectInsideBatch(SelectableObject* selectableObject);

        std::vector<SelectableObject*> selectablesCache;
        SelectableObject* selectedRecently{nullptr};
        SelectableObject* hoveredRecently{nullptr};
        
        void notifyAllOnSelect(SelectableObject* selObj) {
            for (auto listener : listeners) {
                listener->onSelectableObjectGoSelected(selObj);
            }
        }

        void notifyAllOnNormal(SelectableObject* selObj) {
            for (auto listener : listeners) {
                listener->onSelectableObjectGoNormal(selObj);
            }
        }

        std::vector<SelectableObjectListener*> listeners;
    };

}
