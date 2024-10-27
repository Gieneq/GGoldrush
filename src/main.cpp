#include <SFML/Graphics.hpp>

#include <iostream>

#include <gui/guis/game/GameGUI.hpp>
#include <gui/common/events.hpp>
#include <gui/font/FontManger.hpp>
#include <gui/Debug.hpp>
#include <world/World.hpp>
#include <common/Utils.hpp>


int main() {
    auto window = sf::RenderWindow{ { 3*1920u/4, 3*1080u/4 }, "Some GProject" };
    window.setFramerateLimit(60);
    sf::View windowView = window.getDefaultView();
    const sf::Vector2u minimalSize{800, 600}; 

    std::cout << "Starting" << std::endl;
    gui::DebugOverlay::get().visible = false;

    world::World world({5, 15});
    world.getCamera().sameAs(windowView);
    world.getCamera().lookAt({0,0});

    gui::GameGUI gameGUI(window);
    gui::ClickEventsExtractor clicEventsExtractor;

    sf::Clock loopTimeMeasure;

    while (window.isOpen()) {
        gui::DebugOverlay::get().clear();

        for (auto event = sf::Event{}; window.pollEvent(event);) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1) {
                gui::DebugOverlay::get().visible = !gui::DebugOverlay::get().visible;
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F2) {
                gameGUI.setScale(gameGUI.getScale() + 10.0F);
            } 
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F3) {
                gameGUI.setScale(gameGUI.getScale() - 10.0F);
            } 
            else if (event.type == sf::Event::Resized) {
                if (event.size.width < minimalSize.x) {
                    event.size.width = minimalSize.x;
                    window.setSize({event.size.width, window.getSize().y});
                }
                if (event.size.height < minimalSize.y) {
                    event.size.height = minimalSize.y;
                    window.setSize({window.getSize().x, event.size.height});
                }

                const float newWidth = static_cast<float>(event.size.width);
                const float newHeight = static_cast<float>(event.size.height);
                std::cout << "Resized to: " << newWidth << " x " << newHeight << std::endl;
                windowView.setSize(newWidth, newHeight);
                windowView.setCenter({newWidth/2, newHeight/2});
                gameGUI.setPosition(0, 0, newWidth, newHeight);
                
                world.getCamera().sameAs(windowView);
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
                    gameGUI.processEvents(clickEventResult.value());
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
        window.setView(windowView);
        gameGUI.tick(deltaTimeSec);
        gameGUI.validate();
        gameGUI.draw(window);
        gui::DebugOverlay::get().draw(window);
        window.display();
    }
}
