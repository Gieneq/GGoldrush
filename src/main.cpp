#include <SFML/Graphics.hpp>

#include <iostream>

#include <gui/view/View.hpp>
#include <gui/common/events.hpp>
#include <gui/font/FontManger.hpp>
#include <world/World.hpp>


int main() {
    auto window = sf::RenderWindow{ { 1920u/2, 1080u/2 }, "Some GProject" };
    window.setFramerateLimit(60);

    std::cout << "Starting" << std::endl;

    world::World world({5, 5});
    world.getCamera().sameAs(window.getDefaultView());
    world.getCamera().lookAt({0,0});

    gui::View view(window);
    gui::ClickEventsExtractor clicEventsExtractor;

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {

            if (event.type == sf::Event::Closed) {
                window.close();
            } 
            else {

                /* Extract GUI events from common events */
                const auto mousePosition = sf::Mouse::getPosition(window);

                const auto clickEventResult = clicEventsExtractor.extract(event, mousePosition);
                if (clickEventResult.has_value()) {
                    view.processEvents(clickEventResult.value());
                }

            }

        }

        window.clear();

        /* World */
        window.setView(world.getCamera().getView());
        world.tick();
        world.draw(window);

        /* GUI ontop */
        window.setView(window.getDefaultView());
        view.tick();
        // view.draw(window);
        
        window.display();
    }
}
