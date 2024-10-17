#include <gtest/gtest.h>
#include "game/items/Item.hpp"

using namespace game;

TEST(ItemTest, TestItemCreation) {
    // Arrange
    ItemsManager& manager = ItemsManager::get();

    // Act
    Item item1 = manager.createItem(ItemType::RAW_WOOD, 10);

    // Assert
    ASSERT_EQ(item1.getQuantity(), 10);
    ASSERT_EQ(item1.meta.name, "Raw Wood");
}

TEST(ItemTest, TestItemAddition) {
    // Arrange
    ItemsManager& manager = ItemsManager::get();

    Item item1 = manager.createItem(RAW_WOOD, 10);  // 10 units of wood
    Item item2 = manager.createItem(RAW_WOOD, 5);   // 5 units of wood

    // Act
    item1 += item2;

    // Assert
    ASSERT_EQ(item1.getQuantity(), 15);  // 10 + 5 should be 15
}

TEST(ItemTest, TestItemComparison) {
    // Arrange
    ItemsManager& manager = ItemsManager::get();

    Item item1 = manager.createItem(RAW_WOOD, 10);
    Item item2 = manager.createItem(RAW_WOOD, 5);

    // Assert
    ASSERT_TRUE(item1 > item2);  // 10 > 5
    ASSERT_FALSE(item1 == item2);  // 10 != 5
}

TEST(ItemTest, TestItemExceptionOnNegativeQuantity) {
    // Arrange
    ItemsManager& manager = ItemsManager::get();
    // manager.addItemMeta(RAW_WOOD, FOREST, "Raw Wood", "A piece of raw wood", 0);

    Item item = manager.createItem(RAW_WOOD, 10);

    // Act & Assert
    EXPECT_THROW(item.setQuantity(-5), Item::ItemsQuantityException);  // Should throw on negative quantity
}
