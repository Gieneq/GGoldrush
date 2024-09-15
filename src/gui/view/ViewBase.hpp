#pragma once

#include <SFML/Graphics.hpp>

#include <gui/container/Container.hpp>

#include <gui/button/GenericButton.hpp>


namespace gui {

    class ViewBase : public Container, protected ButtonClickListener {
    public:
        ViewBase();

    protected:
        virtual void onButtonClicked(gui::GenericButton* button) override {}
    };
}