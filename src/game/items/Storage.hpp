#pragma once

#include <optional>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>

#include "Item.hpp"

namespace game {
    
    class Storage {
    public:

        class Quantity {
        public:
            class QuantityAllValueException : public std::logic_error {
            public:
                QuantityAllValueException() : std::logic_error("Attempted to get quantity when 'ALL' was specified.") {}
            };

            Quantity() : quantityOption{std::nullopt} {}
            Quantity(int quantity) : quantityOption{quantity} {} // explicit would not allow using just int as constructor

            static Quantity ALL() {
                return Quantity();
            }

            bool isAll() const {
                return !quantityOption.has_value();
            }

            // Get the specific quantity (only valid if not "ALL")
            int getQuantity() const {
                if (!quantityOption.has_value()) {
                    throw QuantityAllValueException();
                }
                return quantityOption.value();
            }

        private:
            std::optional<int> quantityOption;
        };


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

        Storage(Quantity slotsMaxCount = Quantity::ALL(), Quantity itemsMaxCount = Quantity::ALL()) 
            : slotsMaxCount{slotsMaxCount}, itemsMaxCount{itemsMaxCount} {}
        virtual ~Storage() = default;

        void add(Item&& other);

        Item extract(ItemType type, Quantity quantity = Quantity::ALL());
        
        void moveItemTo(ItemType type, Storage& destinationStorage, Quantity quantity = Quantity::ALL());

        // Add iterator support (range-based for loop)
        auto begin() { return items.begin(); }
        auto end() { return items.end(); }

        // For const iteration (range-based for loop in const context)
        auto begin() const { return items.cbegin(); }
        auto end() const { return items.cend(); }

        int getOverallItemsCount() const {
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
        Quantity slotsMaxCount;
        Quantity itemsMaxCount;
        int recentItemsCount{0};
    };


    // class SlotsLimitedStorage : public Storage {

    // };

    // class CapacityLimitedStorage : public Storage {

    // };
}
