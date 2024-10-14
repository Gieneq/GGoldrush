#pragma once

#include <SFML/Graphics.hpp>

#include "Properties.hpp"

#include <iostream>
#include <sstream>

namespace utils {

    class PeakDetector {
    public:
        PeakDetector(float alpha = 0.01f)
            : maxValue(0.0f), alpha(alpha) {}

        void updateValue(float newValue) {
            if (newValue > maxValue) {
                maxValue = newValue;  // Set new max time immediately if the new time is greater
            } else {
                maxValue = (1.0f - alpha) * maxValue + alpha * newValue;  // Apply RC filter
            }
        }

        float getMaxValue() const {
            return maxValue;
        }

    private:
        float maxValue; 
        float alpha;    // Smoothing factor (like an RC filter constant)
    };
}

template <class T>
inline std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vec) {
    return os << "[" << vec.x << ", " << vec.y << "]";
}

inline std::ostream& operator<<(std::ostream& os, const sf::Vector2i& vec) {
    return os << "[" << vec.x << ", " << vec.y << "]";
}

