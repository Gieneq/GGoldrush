#include <gtest/gtest.h>
#include <gui/box/Box.hpp>
#include <gui/container/Container.hpp>

using namespace gui;

class BoxTest : public Box {
    public:
        BoxTest() : Box() {}
        BoxTest(const Box& box) : Box(box) {}
        using Box::getShape;
        using Box::isValid;
};

class ContainerCustomizedTest : public Container {
    public:

        ContainerCustomizedTest() : Container() {
            add(&boxLeftAligned);
            add(&boxRightAligned);
        }
        
        virtual void recalculate() {
            recalculatesCount++;

            boxLeftAligned.setPosition(0, 0, 50, 80);

            const float boxWidth = 70;
            const auto rightX = getWidth() - boxWidth;
            boxRightAligned.setPosition(rightX, 0, boxWidth, 110);

            Container::recalculate();
            //todo consider using 2 recalculates
        }

        BoxTest boxLeftAligned;
        BoxTest boxRightAligned;

        int recalculatesCount{0};

        using Container::isValid;
        using Container::getBackground;

};

TEST(GUITest, TestCustiomizedContainerAlignmentRecalculation) {
    ContainerCustomizedTest custCnt1;

    /* Initial resize */
    custCnt1.setWidth(200);
    custCnt1.setHeight(100);
    ASSERT_EQ(custCnt1.isValid(), false);

    custCnt1.validate();
    
    ASSERT_EQ(custCnt1.boxLeftAligned.hasParent(), true);
    ASSERT_EQ(custCnt1.boxRightAligned.hasParent(), true);
    
    ASSERT_EQ(custCnt1.isValid(), true);
    ASSERT_EQ(custCnt1.recalculatesCount, 1);
    ASSERT_EQ(custCnt1.boxLeftAligned.getX(), 0);
    ASSERT_EQ(custCnt1.boxLeftAligned.getY(), 0);
    ASSERT_EQ(custCnt1.boxLeftAligned.getWidth(), 50);
    ASSERT_EQ(custCnt1.boxLeftAligned.getHeight(), 80);

    const float rightBoxWidth = 70;
    const float rightBoxLeft1 = 200 - rightBoxWidth;
    ASSERT_EQ(custCnt1.boxRightAligned.getX(), rightBoxLeft1);
    ASSERT_EQ(custCnt1.boxRightAligned.getY(), 0);
    ASSERT_EQ(custCnt1.boxRightAligned.getWidth(), rightBoxWidth);
    ASSERT_EQ(custCnt1.boxRightAligned.getHeight(), 110);
    
    ASSERT_EQ(custCnt1.boxLeftAligned.getShape().getGlobalBounds().left, 0);
    ASSERT_EQ(custCnt1.boxRightAligned.getShape().getGlobalBounds().left, rightBoxLeft1);

    /* Next resize */
    custCnt1.setWidth(90);
    ASSERT_EQ(custCnt1.isValid(), false);

    custCnt1.validate();
    
    const float rightBoxLeft2 = 90 - rightBoxWidth;
    ASSERT_EQ(custCnt1.isValid(), true);
    ASSERT_EQ(custCnt1.recalculatesCount, 2);
    ASSERT_EQ(custCnt1.boxLeftAligned.getX(), 0);
    ASSERT_EQ(custCnt1.boxRightAligned.getX(), rightBoxLeft2);
    ASSERT_EQ(custCnt1.boxRightAligned.getWidth(), rightBoxWidth);
    
    ASSERT_EQ(custCnt1.boxLeftAligned.getShape().getGlobalBounds().left, 0);
    ASSERT_EQ(custCnt1.boxRightAligned.getShape().getGlobalBounds().left, rightBoxLeft2);
}