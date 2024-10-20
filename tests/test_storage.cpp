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
    Storage storage(Storage::Quantity::ALL(), 10);  // Limit item count to 10

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

TEST(StorageTest, AddSameItemTypeMultipleTimes) {
    Storage storage;

    // Add RAW_WOOD with quantity 5, then add another RAW_WOOD with quantity 3
    storage.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 5));
    storage.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 3));

    ASSERT_EQ(storage[ItemType::RAW_WOOD].getQuantity(), 8);  // Quantities should be summed
    ASSERT_EQ(storage.getOccupiedSlotsCount(), 1);  // Only one slot should be occupied
    ASSERT_EQ(storage.getOverallItemsCount(), 8);  // Total quantity should be 8
}

TEST(StorageTest, AddDifferentItemTypes) {
    Storage storage;

    // Add RAW_WOOD and PLANK with different quantities
    storage.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 7));
    storage.add(ItemsManager::get().createItem(ItemType::PLANK, 3));

    ASSERT_EQ(storage[ItemType::RAW_WOOD].getQuantity(), 7);
    ASSERT_EQ(storage[ItemType::PLANK].getQuantity(), 3);
    ASSERT_EQ(storage.getOccupiedSlotsCount(), 2);  // Two different items, so two slots should be occupied
    ASSERT_EQ(storage.getOverallItemsCount(), 10);  // Total quantity should be 7 + 3 = 10
}

TEST(StorageTest, ExceedingSlotCountThrowsException) {
    Storage storage(2, Storage::Quantity::ALL());  // Limit to 2 slots, unlimited items

    storage.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 3));
    storage.add(ItemsManager::get().createItem(ItemType::PLANK, 2));

    // Adding a third item type should exceed the slot count
    Item item = ItemsManager::get().createItem(ItemType::TABLE, 1);
    EXPECT_THROW(storage.add(std::move(item)), game::Storage::NoSlotsException);
}

TEST(StorageTest, ExtractAllItems) {
    Storage storage;
    storage.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 10));

    // Extract all items
    Item extractedItem = storage.extract(ItemType::RAW_WOOD, Storage::Quantity::ALL());

    ASSERT_EQ(extractedItem.getQuantity(), 10);  // All 10 items should be extracted
    ASSERT_EQ(storage.getOccupiedSlotsCount(), 0);  // No slots should be occupied
    ASSERT_EQ(storage.getOverallItemsCount(), 0);  // Total quantity should be 0
}

TEST(StorageTest, ExtractPartialItems) {
    Storage storage;
    storage.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 10));

    // Extract 4 items
    Item extractedItem = storage.extract(ItemType::RAW_WOOD, 4);

    ASSERT_EQ(extractedItem.getQuantity(), 4);  // 4 items should be extracted
    ASSERT_EQ(storage[ItemType::RAW_WOOD].getQuantity(), 6);  // 6 items should remain
    ASSERT_EQ(storage.getOccupiedSlotsCount(), 1);  // The slot should still be occupied
    ASSERT_EQ(storage.getOverallItemsCount(), 6);  // Total quantity should now be 6
}

TEST(StorageTest, MoveAllItemsBetweenStorages) {
    Storage storageFrom;  
    Storage storageTo;

    // Setup storage
    storageFrom.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 10));
    storageFrom.moveItemTo(ItemType::RAW_WOOD, storageTo, Storage::Quantity::ALL());

    ASSERT_EQ(storageFrom.getOccupiedSlotsCount(), 0);  // Source storage should be empty
    ASSERT_EQ(storageTo[ItemType::RAW_WOOD].getQuantity(), 10);  // Destination should now have all items
    ASSERT_EQ(storageTo.getOverallItemsCount(), 10);  // Total quantity should be 10 in the destination
}

TEST(StorageTest, ExtractMoreThanAvailableThrowsException) {
    Storage storage;
    storage.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 5));

    // Attempt to extract more than available should throw an exception
    EXPECT_THROW(storage.extract(ItemType::RAW_WOOD, 10), game::Item::QuantityException);
}

TEST(StorageTest, AddEmptyItemNotThrowsException) {
    Storage storage;
    storage.add(std::move(ItemsManager::get().createItem(ItemType::RAW_WOOD, 0)));
    ASSERT_EQ(storage.getOccupiedSlotsCount(), 0);
    ASSERT_EQ(storage.getOverallItemsCount(), 0);  
    EXPECT_THROW(storage[ItemType::RAW_WOOD].getQuantity(), Storage::ItemNotFoundException); 
}

TEST(StorageTest, MoveAnyItemsPossibleBetweenStorages) {
    Storage storageFrom;  
    Storage storageTo{2, 20};

    // Setup storage
    storageFrom.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 10));
    storageFrom.add(ItemsManager::get().createItem(ItemType::PLANK, 4));

    storageFrom.moveAnyItemsTo(storageTo);

    ASSERT_EQ(storageFrom.getOccupiedSlotsCount(), 0); 
    ASSERT_EQ(storageFrom.getOverallItemsCount(), 0); 
    EXPECT_THROW(storageFrom[ItemType::RAW_WOOD].getQuantity(), Storage::ItemNotFoundException); 
    EXPECT_THROW(storageFrom[ItemType::PLANK].getQuantity(), Storage::ItemNotFoundException); 
    ASSERT_EQ(storageFrom.getQuantityOf(ItemType::RAW_WOOD), 0); 
    ASSERT_EQ(storageFrom.getQuantityOf(ItemType::PLANK), 0);

    ASSERT_EQ(storageTo.getOccupiedSlotsCount(), 2); 
    ASSERT_EQ(storageTo.getOverallItemsCount(), 14); 
    ASSERT_EQ(storageTo[ItemType::RAW_WOOD].getQuantity(), 10); 
    ASSERT_EQ(storageTo[ItemType::PLANK].getQuantity(), 4); 
    ASSERT_EQ(storageTo.getQuantityOf(ItemType::RAW_WOOD), 10); 
    ASSERT_EQ(storageTo.getQuantityOf(ItemType::PLANK), 4);  
}

TEST(StorageTest, MoveAnyItemsPossibleBetweenStoragesWhileNotEnoughSpace) {
    Storage storageFrom;  
    Storage storageTo{2, 12};

    // Setup storage
    storageFrom.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 10));
    storageFrom.add(ItemsManager::get().createItem(ItemType::PLANK, 4));

    storageFrom.moveAnyItemsTo(storageTo);

    ASSERT_EQ(storageFrom.getOccupiedSlotsCount(), 1); 
    ASSERT_EQ(storageFrom.getOverallItemsCount(), 2); 
    EXPECT_THROW(storageFrom[ItemType::RAW_WOOD].getQuantity(), Storage::ItemNotFoundException); 
    ASSERT_EQ(storageFrom.getQuantityOf(ItemType::PLANK), 2);

    ASSERT_EQ(storageTo.getOccupiedSlotsCount(), 2); 
    ASSERT_EQ(storageTo.getOverallItemsCount(), 12); 
    ASSERT_EQ(storageTo[ItemType::RAW_WOOD].getQuantity(), 10); 
    ASSERT_EQ(storageTo[ItemType::PLANK].getQuantity(), 2); 
}

TEST(StorageTest, MoveAnyItemsPossibleBetweenStoragesWhileNotEnoughSlots) {
    Storage storageFrom;  
    Storage storageTo{1, 12};

    // Setup storage
    storageFrom.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 10));
    storageFrom.add(ItemsManager::get().createItem(ItemType::PLANK, 4));

    storageFrom.moveAnyItemsTo(storageTo);

    ASSERT_EQ(storageFrom.getOccupiedSlotsCount(), 1); 
    ASSERT_EQ(storageFrom.getOverallItemsCount(), 4); 
    EXPECT_THROW(storageFrom[ItemType::RAW_WOOD].getQuantity(), Storage::ItemNotFoundException); 
    ASSERT_EQ(storageFrom.getQuantityOf(ItemType::PLANK), 4);

    ASSERT_EQ(storageTo.getOccupiedSlotsCount(), 1); 
    ASSERT_EQ(storageTo.getOverallItemsCount(), 10); 
    ASSERT_EQ(storageTo[ItemType::RAW_WOOD].getQuantity(), 10); 
    EXPECT_THROW(storageTo[ItemType::PLANK].getQuantity(), Storage::ItemNotFoundException); 
}

TEST(StorageTest, MoveAnyItemsPossibleBetweenStoragesWhileTargetHasSlotToFillup) {
    Storage storageFrom;  
    Storage storageTo{2, 20};

    // Setup storage
    storageFrom.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 10));
    storageFrom.add(ItemsManager::get().createItem(ItemType::PLANK, 4));

    storageTo.add(ItemsManager::get().createItem(ItemType::PLANK, 5));
    storageTo.add(ItemsManager::get().createItem(ItemType::RAW_WOOD, 3));

    storageFrom.moveAnyItemsTo(storageTo);

    ASSERT_EQ(storageFrom.getOccupiedSlotsCount(), 1); 
    ASSERT_EQ(storageFrom.getOverallItemsCount(), 2); 
    EXPECT_THROW(storageFrom[ItemType::RAW_WOOD].getQuantity(), Storage::ItemNotFoundException); 
    ASSERT_EQ(storageFrom.getQuantityOf(ItemType::PLANK), 2);

    ASSERT_EQ(storageTo.getOccupiedSlotsCount(), 2); 
    ASSERT_EQ(storageTo.getOverallItemsCount(), 20); 
    ASSERT_EQ(storageTo[ItemType::RAW_WOOD].getQuantity(), 13); 
    ASSERT_EQ(storageTo[ItemType::PLANK].getQuantity(), 7); 
}
