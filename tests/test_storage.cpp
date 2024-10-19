#include "game/items/Storage.hpp"
#include "game/items/Item.hpp"
#include <gtest/gtest.h>

using namespace game;

TEST(StorageTest, AddItem) {
    Storage storage; 

    storage.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 10));

    ASSERT_EQ(storage[ItemType::RAW_WOOD].getMeta()->type, ItemType::RAW_WOOD);
    ASSERT_EQ(storage[ItemType::RAW_WOOD].getQuantity(), 10);
    ASSERT_EQ(storage.getOccupiedSlotsCount(), 1);
    ASSERT_EQ(storage.getOverallItemsCount(), 10);
}

TEST(StorageTest, ExceedingCapacityThrowsException) {
    Storage storage(std::nullopt, 10);  // Limit item count to 10

    Item item1 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 8);
    Item item2 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 2);
    Item item3 = ItemsManager::get().createItem(ItemType::RAW_WOOD, 1);

    storage.add(std::move(item1));
    storage.add(std::move(item2));
    ASSERT_TRUE(item1.isCorrupted());
    ASSERT_TRUE(item1.isCorrupted());
    EXPECT_THROW(storage.add(std::move(item3)), game::Storage::NoCapacityException);
}

TEST(StorageTest, MoveItemBetweenStorages) {
    Storage storageFrom;  
    Storage storageTo;

    // Setup storage
    storageFrom.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 8));
    storageFrom.moveItemTo(ItemType::RAW_WOOD, storageTo, 6);
    
    ASSERT_EQ(storageFrom[ItemType::RAW_WOOD].getQuantity(), 2);
    ASSERT_EQ(storageTo[ItemType::RAW_WOOD].getQuantity(), 6);
}