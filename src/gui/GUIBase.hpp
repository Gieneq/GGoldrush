#pragma once

#include <SFML/Graphics.hpp>

#include <gui/container/Container.hpp>

#include <gui/button/GenericButton.hpp>


namespace gui {

    class GUIBase : public Container, protected ButtonClickListener {
    public:
        GUIBase();

    protected:
        virtual void onButtonClicked(gui::GenericButton* button) override {}
    };
}