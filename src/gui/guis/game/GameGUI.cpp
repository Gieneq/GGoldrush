// #include "GameGUI.hpp"

// #include <iostream>

// #include <string>

// namespace gui {

//     GameGUI::GameGUI(const sf::RenderWindow& window) : GUIBase() {
//         setParent(nullptr);
//         setPosition(0, 0, window.getSize().x, window.getSize().y);

//         add(&actionbar);
//     }
    
//     void GameGUI::onButtonClicked(gui::GenericButton* button) {
//         std::cout << "Button clicked: " << *button << std::endl;
//     }

    
//     void GameGUI::setWidth(float width) {
//         // cnt1.setWidth(width - 32);
//         GUIBase::setWidth(width);
//     }

// }