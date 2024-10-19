#pragma once

#include <optional>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>

#include "Item.hpp"

namespace game {
    
    class Storage {
    public:

        class NoCapacityException : public std::runtime_error {
        public:
            NoCapacityException() : std::runtime_error("Storage has no more capacity") {}
        };


        class NoSlotsException : public std::runtime_error {
        public:
            NoSlotsException() : std::runtime_error("Storage has no more slots") {}
        };
        

        class ItemNotFoundException : public std::runtime_error {
        public:
            ItemNotFoundException() : std::runtime_error("No item todo in storage") {}
        };

        Storage(std::optional<size_t> slotsMaxCount = std::nullopt, std::optional<size_t> itemsMaxCount = std::nullopt) 
            : slotsMaxCount{slotsMaxCount}, itemsMaxCount{itemsMaxCount} {}
        virtual ~Storage() = default;

        void add(Item&& other);

        Item extract(ItemType type, std::optional<int> quantityOption = std::nullopt);
        
        void moveItemTo(ItemType type, Storage& destinationStorage, std::optional<int> quantityOption = std::nullopt);

        // Add iterator support (range-based for loop)
        auto begin() { return items.begin(); }
        auto end() { return items.end(); }

        // For const iteration (range-based for loop in const context)
        auto begin() const { return items.cbegin(); }
        auto end() const { return items.cend(); }

        size_t getOverallItemsCount() const {
            return recentItemsCount;
        }

        size_t getOccupiedSlotsCount() const {
            return items.size();
        }

        Item& operator[](ItemType type) {
            auto it = items.find(type);
            if (it == items.end()) {
                throw ItemNotFoundException();
            }
            return it->second;
        }

    protected:
        std::unordered_map<ItemType, Item> items;
        std::optional<size_t> slotsMaxCount;
        std::optional<size_t> itemsMaxCount;
        size_t recentItemsCount{0};
    };


    // class SlotsLimitedStorage : public Storage {

    // };

    // class CapacityLimitedStorage : public Storage {

    // };
}
