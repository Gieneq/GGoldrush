#pragma once

#include <optional>
#include <vector>
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

        void add(const Item& other) {
            if (itemsMaxCount.has_value()) {
                if (recentItemsCount + other.getQuantity() > itemsMaxCount.value()) {
                    throw NoCapacityException();
                }
            }

            auto it = std::find_if(items.begin(), items.end(), [&other](const Item& item){
                return item.meta == other.meta;
            });

            if (it != items.end()) {
                *it += other;
            } else {
                if (slotsMaxCount.has_value()) {
                    if (items.size() > slotsMaxCount.value()) {
                        throw NoSlotsException();
                    }

                    items.push_back(other);
                }
            }
        }

        void retrive(const Item& other) {
            auto it = std::find_if(items.begin(), items.end(), [&other](const Item& item){
                return other.meta == item.meta;
            });

            if (it == items.end()) {
                throw ItemNotFoundException();
            }

            if (*it < other) {
                
            }
        }
        
        // Add iterator support (range-based for loop)
        auto begin() { return items.begin(); }
        auto end() { return items.end(); }

        // For const iteration (range-based for loop in const context)
        auto begin() const { return items.cbegin(); }
        auto end() const { return items.cend(); }

        Item& operator[](ItemType type) {
            auto it = std::find_if(items.begin(), items.end(), [type](Item& item){
                return item.meta.type == type;
            });

            if (it == items.end()) {
                throw ItemNotFoundException();
            }

            return *it;
        }

    protected:
        std::vector<Item> items;
        std::optional<size_t> slotsMaxCount;
        std::optional<size_t> itemsMaxCount;
        size_t recentItemsCount{0};
    };


    // class SlotsLimitedStorage : public Storage {

    // };

    // class CapacityLimitedStorage : public Storage {

    // };
}
