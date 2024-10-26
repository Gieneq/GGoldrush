#include "Container.hpp"


namespace gui {

    Container::Container() : Drawable(), visible{true} {
        background.setParent(this);
        setWidth(60);
        setHeight(30);
    }

    void Container::add(Drawable* drawable) {
        drawable->setParent(this);
        drawables.push_back(drawable);
    }

    void Container::tick(float dt) {
        if (isVisible()) {
            for (auto drawable: drawables) {
                drawable->tick(dt);
            }
        }
    }

    void Container::draw(sf::RenderWindow& target) {
        if (isVisible()) {
            background.draw(target);
            for (auto drawable: drawables) {
                drawable->draw(target);
            }
        }
    }
    
    void Container::processEvents(const gui::ClickEvent& event) {
        if (isVisible() && isTouchable()) {
            for (auto drawable: drawables) {
                drawable->processEvents(event);
            }
        }
    }
    
    // void Container::onResize(float newWidth, float newHeight) {
    //     background.onResize(newWidth, newHeight);
    //     background.setWidth(getWidth());
    //     background.setHeight(getHeight());
    //     for (auto drawable: drawables) {
    //         drawable->onResize(newWidth, newHeight);
    //     }
    // }

    void Container::validate() {
        Drawable::validate();
        background.validate();

        for (auto drawable: drawables) {
            drawable->validate();
        }
    }

    void Container::invalidate() {
        Drawable::invalidate();
        background.invalidate();
        for (auto drawable: drawables) {
            drawable->invalidate();
        }
    }
    
}