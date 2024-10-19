#include "Storage.hpp"

#include <iostream>

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
            throw;
        } catch (const Item::QuantityException&) {
            std::cerr << "Invalid quantity requested from the source storage.\n";
            throw;
        }
    }

}