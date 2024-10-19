#include <gtest/gtest.h>
#include "game/items/Item.hpp"

using namespace game;

TEST(ItemTest, TestItemCreation) {
    Item item1 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 10);

    ASSERT_EQ(item1.getQuantity(), 10);
    ASSERT_EQ(item1.getMeta()->type, ItemType::RAW_WOOD);
}

TEST(ItemTest, TestItemAddition) {
    Item item1 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 10);
    Item item2 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 5);

    Item item3 = item1 + std::move(item2);

    ASSERT_EQ(item3.getQuantity(), 15);  // 10 + 5 should be 15

    ASSERT_TRUE(item1.isCorrupted()); // should be left corrupted
    ASSERT_EQ(item1.getQuantity(), 0); 
    
    ASSERT_TRUE(item2.isCorrupted()); // should be left corrupted
    ASSERT_EQ(item2.getQuantity(), 0); 
}

TEST(ItemTest, TestItemSubtraction) {
    Item item1 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 10);
    Item item2 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 5);

    Item item3 = item1 - std::move(item2);

    ASSERT_EQ(item3.getQuantity(), 5);  // 10 - 5 should be 5

    ASSERT_TRUE(item1.isCorrupted()); // should be left corrupted
    ASSERT_EQ(item1.getQuantity(), 0);

    ASSERT_TRUE(item2.isCorrupted()); // should be left corrupted
    ASSERT_EQ(item2.getQuantity(), 0);
}

TEST(ItemTest, TestItemAdditionWithMove) {
    Item item1 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 10);
    Item item2 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 5);

    // Use operator+= to add item2 to item1, item2 should be corrupted after
    item1 += std::move(item2);

    // Check the resulting quantity of item1
    ASSERT_EQ(item1.getQuantity(), 15);  // 10 + 5 should be 15

    // Check that item2 is corrupted after the operation
    ASSERT_TRUE(item2.isCorrupted());
    ASSERT_EQ(item2.getQuantity(), 0);
}

TEST(ItemTest, TestItemAdditionWithQuantity) {
    Item item1 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 10);

    // Use operator+= to add a quantity to item1
    item1 += 5;

    // Check the resulting quantity of item1
    ASSERT_EQ(item1.getQuantity(), 15);  // 10 + 5 should be 15
}

TEST(ItemTest, TestItemSubtractionWithMove) {
    Item item1 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 10);
    Item item2 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 5);

    // Use operator-= to subtract item2 from item1, item2 should be corrupted after
    item1 -= std::move(item2);

    // Check the resulting quantity of item1
    ASSERT_EQ(item1.getQuantity(), 5);  // 10 - 5 should be 5

    // Check that item2 is corrupted after the operation
    ASSERT_TRUE(item2.isCorrupted());
    ASSERT_EQ(item2.getQuantity(), 0);
}

TEST(ItemTest, TestItemSubtractionWithQuantity) {
    Item item1 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 10);

    // Use operator-= to subtract a quantity from item1
    item1 -= 5;

    // Check the resulting quantity of item1
    ASSERT_EQ(item1.getQuantity(), 5);  // 10 - 5 should be 5
}

TEST(ItemTest, TestItemComparison) {
    Item item1 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 10);
    Item item2 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 5);

    ASSERT_TRUE(item1 > item2);  // 10 > 5
    ASSERT_FALSE(item1 == item2);  // 10 != 5
}

TEST(ItemTest, TestItemExceptionOnNegativeQuantity) {
    Item item = ItemsManager::get().createItem(ItemType::RAW_WOOD, 10);

    EXPECT_THROW(item.setQuantity(-5), Item::QuantityException);  // Should throw on negative quantity
}
