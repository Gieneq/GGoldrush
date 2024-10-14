#include <SFML/Graphics.hpp>

#include <iostream>

#include <gui/view/View.hpp>
#include <gui/common/events.hpp>
#include <gui/font/FontManger.hpp>
#include <gui/Debug.hpp>
#include <world/World.hpp>
#include <common/Utils.hpp>


int main() {
    auto window = sf::RenderWindow{ { 1920u/2, 1080u/2 }, "Some GProject" };
    window.setFramerateLimit(60);

    std::cout << "Starting" << std::endl;

    world::World world({5, 15});
    world.getCamera().sameAs(window.getDefaultView());
    // world.getCamera().lookAt({1920u/4,0});
    world.getCamera().lookAt({0,0});

    gui::View view(window);
    gui::ClickEventsExtractor clicEventsExtractor;

    sf::Clock loopTimeMeasure;

    while (window.isOpen()) {
        gui::DebugOverlay::get().clear();

        for (auto event = sf::Event{}; window.pollEvent(event);) {

            if (event.type == sf::Event::Closed) {
                window.close();
            } 
            else {

                /* Extract GUI events from common events */
                const auto mouseScreenPosition = sf::Mouse::getPosition(window);
                const auto mouseCameraPosition = world.getCamera().transformScrenToCameraSpace(mouseScreenPosition);
                const auto mouseWorldPosition = world::Camera::cameraToWorldSpace(mouseCameraPosition);

                gui::DebugOverlay::get().common.cameraTranslation = world.getCamera().getView().getCenter();
                gui::DebugOverlay::get().common.cameraSize = world.getCamera().getView().getSize();

                gui::DebugOverlay::get().common.mouseScreenSpacePosition = mouseScreenPosition;
                gui::DebugOverlay::get().common.mouseCameraSpacePosition = mouseCameraPosition;
                gui::DebugOverlay::get().common.mouseWorldSpacePosition = mouseWorldPosition;

                /* LMB events */
                const auto clickEventResult = clicEventsExtractor.extract(event, mouseScreenPosition);
                if (clickEventResult.has_value()) {
                    view.processEvents(clickEventResult.value());
                }

                /* Other events */
                world.processEvents(event, mouseScreenPosition);
            }

        }

        window.clear();

        const float deltaTimeSec = loopTimeMeasure.restart().asSeconds();
        gui::DebugOverlay::get().common.deltaTimeSec = deltaTimeSec;

        /* World */
        window.setView(world.getCamera().getView());
        world.tick(deltaTimeSec);
        world.draw(window);

        /* GUI ontop */
        window.setView(window.getDefaultView());
        view.tick(deltaTimeSec);
        view.draw(window);
        gui::DebugOverlay::get().draw(window);
        
        window.display();
    }
}
