#pragma once

#include <SFML/Graphics.hpp>

namespace gui {

    class Scale : sf::NonCopyable {
        Scale() : scale{1.0F} {}

    public:
        static Scale& get() {
            static Scale instance;
            return instance;
        }

        void setValue(float scale) {
            this->scale = scale;
            //TODO consider observers
        }

        float value() const {
            return scale;
        }

    private:
        float scale;    
    };

    namespace style {

        const sf::Color DEFAULT_BG_COLOR{70,70,80};
    } 
    
}
