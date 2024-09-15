#include <SFML/Graphics.hpp>

#include <iostream>

#include <gui/view/View.hpp>
#include <gui/common/events.hpp>

int main() {
    auto window = sf::RenderWindow{ { 1920u/2, 1080u/2 }, "Some GProject" };
    window.setFramerateLimit(60);

    std::cout << "Starting" << std::endl;

    gui::View view(window);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {

            if (event.type == sf::Event::Closed) {
                window.close();
            } 
            else {
                if ((event.type == sf::Event::MouseButtonPressed) || (event.type == sf::Event::MouseButtonReleased)) {
                    
                    const auto mousePosition = sf::Mouse::getPosition(window);

                    const auto clickEventType = event.type == sf::Event::MouseButtonPressed 
                        ? gui::ClickEvent::Type::PRESSED : gui::ClickEvent::Type::RELEASED;

                    const gui::ClickEvent clickEvent(clickEventType, mousePosition);

                    view.processEvents(clickEvent);
                }
            }

        }

        window.clear();

        view.tick();
        view.draw(window);

        window.display();
    }
}
