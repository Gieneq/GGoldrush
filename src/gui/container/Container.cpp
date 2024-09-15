#include "Container.hpp"


namespace gui {

    void Container::add(Drawable* drawable) {
        drawable->setParent(this);
        drawables.push_back(drawable);
    }

}