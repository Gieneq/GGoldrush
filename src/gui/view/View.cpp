#include "View.hpp"

#include <iostream>

#include <string>

namespace gui {

    View::View(const sf::RenderWindow& window) : ViewBase(), btn2{gui::FontManager::Style::LATO_REGULAR, "Hello"} {
        setParent(nullptr);
        setPosition(0, 0, window.getSize().x, window.getSize().y);

        const float offset = 16;

        cnt1.setPosition(offset,offset,getWidth() - 2 * offset, 120);
        add(&cnt1);

        box1.setPosition(0,0,cnt1.getWidth(), cnt1.getHeight());
        cnt1.add(&box1);

        btn1.setPosition(offset, offset, 60, 30);
        cnt1.add(&btn1);
        btn1.setOnClickListener(this);
        
        btn2.setPosition(btn1.getX() + btn1.getWidth() + offset, offset, 2*60, 30);
        cnt1.add(&btn2);
        btn2.setOnClickListener(this);

        std::cout << "CNT1: " << cnt1 << std::endl;
        std::cout << "box1: " << box1 << std::endl;
        std::cout << "btn1: " << btn1 << std::endl;
        std::cout << "btn2: " << btn2 << std::endl;
    }
    
    void View::onButtonClicked(gui::GenericButton* button) {
        std::cout << "Button clicked: " << *button << std::endl;
    }
}