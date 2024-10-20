#include "Container.hpp"


namespace gui {

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

    void Container::invalidate() {
        for (auto drawable: drawables) {
            drawable->invalidate();
        }
    }
}