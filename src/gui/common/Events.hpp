#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <sstream>
#include <optional>

namespace gui {

    class ClickEvent {
    public:
        enum Type {
            PRESSED,
            RELEASED,
            DRAG,
            MOVE
        };

        ClickEvent(Type type, const sf::Vector2i& mousePosition) 
            : type(type), mousePosition(mousePosition) {}

        Type type;
        sf::Vector2i mousePosition;

        static std::string getEventTypeName(Type type) {
            switch (type) {
            case Type::PRESSED:
                return "PRESSED";

            case Type::RELEASED:
                return "RELEASED";

            case Type::DRAG:
                return "DRAG";

            case Type::MOVE:
                return "MOVE";
            
            default:
                return "Unknown";
            }
        }

        virtual std::string toString() const {
            std::ostringstream ss;
            ss << "ClickEvent" << getEventTypeName(type) << ", mouse = (" << mousePosition.x << ", " << mousePosition.y << ")";
            return ss.str();
        }
    };

    class ClickEventsExtractor {
    public:
        using ExtractResult = std::optional<ClickEvent>;
        
        ClickEventsExtractor() {}

        ExtractResult extract(const sf::Event& event, const sf::Vector2i& mousePosition) {
            
            switch (event.type) {

            case sf::Event::MouseButtonPressed: {

                // std::cout << "MMp " << event.mouseButton.x << "/ " << event.mouseButton.y << std::endl;
                
                /* Detect LMB events */
                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    recentlyLMBPressed = true;
                    lastLMBPressedMousePosition = mousePosition;
                    return std::make_optional<gui::ClickEvent>(gui::ClickEvent::Type::PRESSED, mousePosition);
                }

                break;
            }

            case sf::Event::MouseButtonReleased: {

                // std::cout << "MMr " << event.mouseButton.x << "/ " << event.mouseButton.y << std::endl;

                /* Detect LMB events */
                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    recentlyLMBPressed = false;
                    return std::make_optional<gui::ClickEvent>(gui::ClickEvent::Type::RELEASED, mousePosition);
                }

                break;
            }

            case sf::Event::MouseMoved: {

                // std::cout << "MM " << event.mouseMove.x << "/ " << event.mouseMove.y << std::endl;

                if (recentlyLMBPressed) {
                    const auto deltaMousePosition = mousePosition - lastLMBPressedMousePosition;
                    return std::make_optional<gui::ClickEvent>(gui::ClickEvent::Type::DRAG, mousePosition);
                } 
                else {
                    return std::make_optional<gui::ClickEvent>(gui::ClickEvent::Type::MOVE, mousePosition);
                }

                break;
            }
            
            default:
                break;
            }

            return {};
        }

    private:
        bool recentlyLMBPressed{false};

        sf::Vector2i lastLMBPressedMousePosition;
    };

    inline std::ostream& operator<<(std::ostream& os, const ClickEvent& event) {
        return os << event.toString();
    }
}