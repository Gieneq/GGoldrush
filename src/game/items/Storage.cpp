#include "Storage.hpp"

#include <iostream>
#include <sstream> 
#include <vector>

namespace game {

    void Storage::add(Item&& other) {
        if (other.getQuantity() == 0) {
            return;
        }
        if (other.isCorrupted()) {
            throw Item::CorruptionException();
        }
        if (!itemsMaxCount.isAll() && recentItemsCount + other.getQuantity() > itemsMaxCount.getQuantity()) {
            throw NoCapacityException();
        }

        auto it = items.find(other.getMeta()->type);
        if (it != items.end()) {
            Item& item = it->second; 
            recentItemsCount += other.getQuantity();
            item += std::move(other);
        } else {
            if (!slotsMaxCount.isAll() && getOccupiedSlotsCount() >= slotsMaxCount.getQuantity()) {
                throw NoSlotsException();
            }

            recentItemsCount += other.getQuantity();
            items.try_emplace(other.getMeta()->type, std::move(other));
        }
    }

    Item Storage::extract(ItemType type, Quantity quantity) {
        auto it = items.find(type);

        if (it == items.end()) {
            throw ItemNotFoundException();
        }

        Item& item = it->second; 

        if (item.getQuantity() == 0) {
            throw Item::QuantityException();
        }

        const int quantityToExtract = !quantity.isAll() ? quantity.getQuantity() : item.getQuantity();

        if (quantityToExtract > item.getQuantity()) {
            // If requested quantity is more than available, throw an exception
            throw Item::QuantityException();
        }

        if (quantityToExtract == item.getQuantity()) {
            // If the whole item is to be extracted, remove it from storage and return
            Item extractedItem = std::move(item);  // Use move semantics to return the item
            items.erase(it);  // Remove the item from the map
        
            recentItemsCount -= quantityToExtract;
            return extractedItem;
        }

        // Otherwise, extract the requested quantity from the item
        Item extractedItem = item.extract(quantityToExtract);  // Extract the requested quantity
        
        recentItemsCount -= quantityToExtract;
        return extractedItem;  // Return the extracted item
    }

    void Storage::moveItemTo(ItemType type, Storage& destinationStorage, Quantity quantity) {
        // Extract the item from the current storage
        if (!quantity.isAll() && quantity.getQuantity() == 0) {
            return;
        }
        try {
            // Try to extract the specified item with the optional quantity from the source storage
            Item extractedItem = extract(type, quantity);

            // Try to add the extracted item to the destination storage
            try {
                destinationStorage.add(std::move(extractedItem));  // Move the item to the destination
            } catch (const NoCapacityException&) {
                // If the destination doesn't have enough capacity, add the item back to the source storage
                std::cerr << "Failed to add item to destination: No capacity available.\n";
                add(std::move(extractedItem));  // Return the item back to the source
                throw;
            } catch (const NoSlotsException&) {
                // If the destination doesn't have enough slots, add the item back to the source storage
                std::cerr << "Failed to add item to destination: No slots available.\n";
                add(std::move(extractedItem));  // Return the item back to the source
                throw;
            }
        } catch (const ItemNotFoundException&) {
            std::cerr << "Item not found in the source storage.\n";
            /* Should not happen - ignore */
        } catch (const Item::QuantityException&) {
            std::cerr << "Invalid quantity requested from the source storage.\n";
            /* Should not happen - ignore */
        }
    }

    void game::Storage::moveAnyItemsTo(Storage& destinationStorage) {
        // Create a temporary list of item types to avoid iterator invalidation during iteration
        std::vector<ItemType> itemsToMove;
        for (const auto& itemEntry : items) {
            itemsToMove.push_back(itemEntry.first);
        }

        // Try to move each item to the destination storage
        for (const auto& itemType : itemsToMove) {
            const int quantityToMove = destinationStorage.itemsMaxCount.isAll() 
            ? getQuantityOf(itemType) 
            : std::min(getQuantityOf(itemType), (destinationStorage.itemsMaxCount.getQuantity() - destinationStorage.getOverallItemsCount()));

            if (quantityToMove > 0) {
                try {
                    moveItemTo(itemType, destinationStorage, quantityToMove);
                } catch (const NoCapacityException&) {
                    throw;
                } catch (const NoSlotsException&) {
                    //just pass
                }
            }
        }
    }

    int Storage::getQuantityOf(ItemType type) const noexcept {
        const auto it = items.find(type);
        if (it == items.end()) {
            return 0;
        }
        return it->second.getQuantity();
    }

    std::string Storage::toString() const {
        std::ostringstream oss;

        if (items.empty()) {
            oss << "Storage is empty.";
            return oss.str();
        }

        // Iterate through the storage and print item type and quantity
        oss << "Storage contents:\n";
        for (const auto& itemEntry : items) {
            const ItemType& itemType = itemEntry.first;
            const Item& item = itemEntry.second;

            oss << "- " << game::ItemsManager::get().findMeta(itemType).name 
                << ": " << item.getQuantity() << "\n";
        }

        return oss.str();
    }

}