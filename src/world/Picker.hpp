#pragma once

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

    private:
        bool isHovered{false};
        bool isSelected{false};

        virtual bool isMouseInsideShape(const sf::Vector2f& mouseCameraPosition) {
            return false;
        }
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


        void processEvents(const sf::Event& event, const sf::Vector2f& mouseCameraPosition);

    private:
        SelectableObject* findSelectableObjectByMouseCameraPosition(const sf::Vector2f& mouseCameraPosition);
        
        bool isSelectableObjectInsideBatch(SelectableObject* selectableObject);

        std::vector<SelectableObject*> selectablesCache;
        SelectableObject* selectedRecently{nullptr};
        SelectableObject* hoveredRecently{nullptr};
        
    };

}
