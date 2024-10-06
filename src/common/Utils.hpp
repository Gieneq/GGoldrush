#pragma once

#include <SFML/Graphics.hpp>

#include "Properties.hpp"

#include <iostream>
#include <sstream>

namespace utils {

}

template <class T>
inline std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vec) {
    return os << "[" << vec.x << ", " << vec.y << "]";
}