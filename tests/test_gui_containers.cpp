#include <gtest/gtest.h>
#include <gui/box/Box.hpp>
#include <gui/container/Container.hpp>

using namespace gui;

class ContainerTest : public Container {
    public:
        using Container::isValid;
        // using Container::validate;
        using Container::getBackground;
};

class BoxTest : public Box {
    public:
        BoxTest() : Box() {}
        BoxTest(const Box& box) : Box(box) {}
        using Box::getShape;
        using Box::isValid;
        // using Box::validate;
};

TEST(GUITest, TestBoxCreationDefault) {
    BoxTest box1{};

    ASSERT_EQ(box1.getX(), 0);
    ASSERT_EQ(box1.getY(), 0);
    ASSERT_EQ(box1.getWidth(), 20);
    ASSERT_EQ(box1.getHeight(), 10);
    ASSERT_EQ(box1.hasParent(), false);
    ASSERT_EQ(box1.getGlobalX(), 0);
    ASSERT_EQ(box1.getGlobalY(), 0);

    ASSERT_EQ(box1.isVisible(), true);
    ASSERT_EQ(box1.isTouchable(), false);
    ASSERT_EQ(box1.isValid(), false);
    
    ASSERT_EQ(box1.getShape().getPosition().x, 0);
    ASSERT_EQ(box1.getShape().getPosition().y, 0);
    ASSERT_EQ(box1.getShape().getSize().x, 20);
    ASSERT_EQ(box1.getShape().getSize().y, 10);
    
    ASSERT_EQ(box1.getShape().getLocalBounds().left, 0);
    ASSERT_EQ(box1.getShape().getLocalBounds().top, 0);
    ASSERT_EQ(box1.getShape().getLocalBounds().width, 20);
    ASSERT_EQ(box1.getShape().getLocalBounds().height, 10);
    
    ASSERT_EQ(box1.getShape().getGlobalBounds().left, 0);
    ASSERT_EQ(box1.getShape().getGlobalBounds().top, 0);
    ASSERT_EQ(box1.getShape().getGlobalBounds().width, 20);
    ASSERT_EQ(box1.getShape().getGlobalBounds().height, 10);
}

TEST(GUITest, TestBoxSetPositionValidate) {
    BoxTest box1{};

    box1.setX(100);
    box1.setY(50);

    ASSERT_EQ(box1.getX(), 100);
    ASSERT_EQ(box1.getY(), 50);
    ASSERT_EQ(box1.getGlobalX(), 100);
    ASSERT_EQ(box1.getGlobalY(), 50); //add invalidating again but with further validate use

    ASSERT_EQ(box1.isValid(), false);
    ASSERT_EQ(box1.getShape().getGlobalBounds().left, 0);
    ASSERT_EQ(box1.getShape().getGlobalBounds().top, 0);
    ASSERT_EQ(box1.getShape().getGlobalBounds().width, 20);
    ASSERT_EQ(box1.getShape().getGlobalBounds().height, 10);

    box1.validate();

    ASSERT_EQ(box1.isValid(), true);
    ASSERT_EQ(box1.getShape().getGlobalBounds().left, 100);
    ASSERT_EQ(box1.getShape().getGlobalBounds().top, 50);
    ASSERT_EQ(box1.getShape().getGlobalBounds().width, 20);
    ASSERT_EQ(box1.getShape().getGlobalBounds().height, 10);
}

TEST(GUITest, TestBoxSetSize) {
    BoxTest box1{};
    
    box1.setWidth(33);

    ASSERT_EQ(box1.isValid(), false);
    ASSERT_EQ(box1.getWidth(), 33);
    ASSERT_EQ(box1.getShape().getGlobalBounds().width, 33);
}

TEST(GUITest, TestBoxSetInvalidatingPosition) {
    BoxTest box1{};

    ASSERT_EQ(box1.isValid(), false);
    ASSERT_EQ(box1.getX(), 0); //default value
    ASSERT_EQ(box1.getShape().getGlobalBounds().left, 0);

    box1.validate();

    ASSERT_EQ(box1.isValid(), true);
    ASSERT_EQ(box1.getX(), 0);
    ASSERT_EQ(box1.getShape().getGlobalBounds().left, 0);
    
    box1.setX(55);
    ASSERT_EQ(box1.isValid(), false);
    ASSERT_EQ(box1.getX(), 55);
    ASSERT_EQ(box1.getShape().getGlobalBounds().left, 0);
    
    box1.validate();
    ASSERT_EQ(box1.isValid(), true);
    ASSERT_EQ(box1.getX(), 55);
    ASSERT_EQ(box1.getShape().getGlobalBounds().left, 55);
}

TEST(GUITest, TestContainerCreate) {
    ContainerTest cnt1;

    ASSERT_EQ(cnt1.isValid(), false);
    ASSERT_EQ(cnt1.getX(), 0);
    ASSERT_EQ(cnt1.getY(), 0);
    ASSERT_EQ(cnt1.getWidth(), 60);
    ASSERT_EQ(cnt1.getHeight(), 30);
    ASSERT_EQ(cnt1.hasParent(), false);
    ASSERT_EQ(cnt1.getGlobalX(), 0);
    ASSERT_EQ(cnt1.getGlobalY(), 0);

    BoxTest bg1{cnt1.getBackground()};

    ASSERT_EQ(bg1.isValid(), false);
    ASSERT_EQ(bg1.getWidth(), 60);
    ASSERT_EQ(bg1.getHeight(), 30);
    ASSERT_EQ(bg1.getShape().getGlobalBounds().left, 0);
    ASSERT_EQ(bg1.getShape().getGlobalBounds().top, 0);
    ASSERT_EQ(bg1.getShape().getGlobalBounds().width, 60);
    ASSERT_EQ(bg1.getShape().getGlobalBounds().height, 30);
}

TEST(GUITest, TestContainerValidating) {
    ContainerTest cnt1;

    cnt1.setX(70);
    cnt1.setY(5);
    cnt1.setWidth(320);
    cnt1.setHeight(90);

    ASSERT_EQ(cnt1.isValid(), false);
    ASSERT_EQ(cnt1.getX(), 70);
    ASSERT_EQ(cnt1.getY(), 5);
    ASSERT_EQ(cnt1.getWidth(), 320);
    ASSERT_EQ(cnt1.getHeight(), 90);
    ASSERT_EQ(cnt1.getGlobalX(), 70);
    ASSERT_EQ(cnt1.getGlobalY(), 5);

    BoxTest bg1Before{cnt1.getBackground()};

    ASSERT_EQ(bg1Before.isValid(), false);
    ASSERT_EQ(bg1Before.getX(), 0);
    ASSERT_EQ(bg1Before.getY(), 0);
    ASSERT_EQ(bg1Before.getGlobalX(), 70);
    ASSERT_EQ(bg1Before.getGlobalY(), 5);
    ASSERT_EQ(bg1Before.getWidth(), 320);
    ASSERT_EQ(bg1Before.getHeight(), 90);
    ASSERT_EQ(bg1Before.getShape().getGlobalBounds().left, 0); // Not updated until validating
    ASSERT_EQ(bg1Before.getShape().getGlobalBounds().top, 0); // Not updated until validating
    ASSERT_EQ(bg1Before.getShape().getGlobalBounds().width, 320);
    ASSERT_EQ(bg1Before.getShape().getGlobalBounds().height, 90);

    cnt1.validate();

    ASSERT_EQ(cnt1.isValid(), true);
    ASSERT_EQ(cnt1.getX(), 70);
    ASSERT_EQ(cnt1.getY(), 5);
    ASSERT_EQ(cnt1.getGlobalX(), 70);
    ASSERT_EQ(cnt1.getGlobalY(), 5);
    ASSERT_EQ(cnt1.getWidth(), 320);
    ASSERT_EQ(cnt1.getHeight(), 90);

    BoxTest bg1After{cnt1.getBackground()};

    ASSERT_EQ(bg1After.isValid(), true);
    ASSERT_EQ(bg1After.getX(), 0);
    ASSERT_EQ(bg1After.getY(), 0);
    ASSERT_EQ(bg1After.getGlobalX(), 70);
    ASSERT_EQ(bg1After.getGlobalY(), 5);
    ASSERT_EQ(bg1After.getWidth(), 320);
    ASSERT_EQ(bg1After.getHeight(), 90);
    ASSERT_EQ(bg1After.getShape().getGlobalBounds().left, 70); // Updated
    ASSERT_EQ(bg1After.getShape().getGlobalBounds().top, 5); // Updated
    ASSERT_EQ(bg1After.getShape().getGlobalBounds().width, 320);
    ASSERT_EQ(bg1After.getShape().getGlobalBounds().height, 90);
}

TEST(GUITest, TestContainerChain) {
    ContainerTest cnt1;
    ContainerTest cnt2;
    BoxTest box2;

    cnt1.add(&cnt2);
    cnt2.add(&box2);

    ASSERT_EQ(cnt1.hasParent(), false);
    ASSERT_EQ(cnt2.hasParent(), true);
    ASSERT_EQ(box2.hasParent(), true);

    cnt1.setPosition(100, 200, 300, 400);
    cnt2.setPosition(10, 20, 30, 40);
    box2.setPosition(1, 2, 3, 4);

    ASSERT_EQ(cnt1.isValid(), false);
    ASSERT_EQ(cnt2.isValid(), false);
    ASSERT_EQ(box2.isValid(), false);

    ASSERT_EQ(cnt1.getGlobalX(), 100);
    ASSERT_EQ(cnt1.getGlobalY(), 200);
    ASSERT_EQ(cnt1.getWidth(), 300);
    ASSERT_EQ(cnt1.getHeight(), 400);

    ASSERT_EQ(cnt2.getGlobalX(), 110);
    ASSERT_EQ(cnt2.getGlobalY(), 220);
    ASSERT_EQ(cnt2.getWidth(), 30);
    ASSERT_EQ(cnt2.getHeight(), 40);

    ASSERT_EQ(box2.getGlobalX(), 111);
    ASSERT_EQ(box2.getGlobalY(), 222);
    ASSERT_EQ(box2.getWidth(), 3);
    ASSERT_EQ(box2.getHeight(), 4);
    
    BoxTest bg1Before{cnt1.getBackground()};
    BoxTest bg2Before{cnt2.getBackground()};
    ASSERT_EQ(bg1Before.getShape().getGlobalBounds().left, 0); // Not updated until validating
    ASSERT_EQ(bg1Before.getShape().getGlobalBounds().top, 0); // Not updated until validating
    ASSERT_EQ(bg2Before.getShape().getGlobalBounds().left, 0); // Not updated until validating
    ASSERT_EQ(bg2Before.getShape().getGlobalBounds().top, 0); // Not updated until validating
    ASSERT_EQ(box2.getShape().getGlobalBounds().left, 0); // Not updated until validating
    ASSERT_EQ(box2.getShape().getGlobalBounds().top, 0); // Not updated until validating

    cnt1.validate(); //Only root

    ASSERT_EQ(cnt1.isValid(), true);
    ASSERT_EQ(cnt2.isValid(), true);
    ASSERT_EQ(box2.isValid(), true);
    
    BoxTest bg1After{cnt1.getBackground()};
    BoxTest bg2After{cnt2.getBackground()};
    ASSERT_EQ(bg1After.getShape().getGlobalBounds().left, 100); // Updated
    ASSERT_EQ(bg1After.getShape().getGlobalBounds().top, 200); // Updated
    ASSERT_EQ(bg2After.getShape().getGlobalBounds().left, 110); // Updated
    ASSERT_EQ(bg2After.getShape().getGlobalBounds().top, 220); // Updated
    ASSERT_EQ(box2.getShape().getGlobalBounds().left, 111); // Updated
    ASSERT_EQ(box2.getShape().getGlobalBounds().top, 222); // Updated
}