#pragma once

#include <SFML/Graphics.hpp>

#include <gui/view/ViewBase.hpp>

#include <gui/button/PlainButton.hpp>
#include <gui/box/Box.hpp>

namespace gui {

    class View : public ViewBase {
    public:
        View(const sf::RenderWindow& window);

    protected:
        void onButtonClicked(gui::GenericButton* button) override;

    private:
        gui::Container cnt1;
        gui::PlainButton btn1;
        gui::Box box1;
    };
    
}


