#pragma once

#include <SFML/Graphics.hpp>

#include <gui/GUIBase.hpp>

// #include <gui/button/PlainButton.hpp>
// #include <gui/button/PlainTextButton.hpp>
#include <gui/box/Box.hpp>

#include "panes/Actionbar.hpp"

namespace gui {

    class GameGUI : public GUIBase {
    public:
        GameGUI(const sf::RenderWindow& window);

    // protected:
    //     void onButtonClicked(gui::GenericButton* button) override;
    virtual void recalculate() {

        const float sf = scale / 100.0F;

        boxleft.setPosition(0, 0, sf * 50, sf * 80);

        boxCenter.setPosition(getWidth() / 2 - (sf * 300) / 2, 10, sf * 300, sf * 90);

        const float boxWidth = sf * 70;
        const auto rightX = getWidth() - boxWidth;
        boxRight.setPosition(rightX, 0, boxWidth, sf * 110);

        Container::recalculate();
        //todo consider using 2 recalculates
    }

    void setScale(float scale) {
        this->scale = std::max(std::min(scale, 200.0F), 50.0F);
        invalidate();
    }

    float getScale() const {
        return scale;
    }

    private:
        // Actionbar actionbar;
        // gui::Container cnt1;
        // gui::PlainButton btn1;
        // gui::PlainTextButton btn2;
        gui::Box boxleft;
        gui::Box boxCenter;
        gui::Box boxRight;

        float scale{100.0F};
    };
    
}


