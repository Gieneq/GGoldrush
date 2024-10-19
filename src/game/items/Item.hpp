#pragma once

#include <iostream>
#include <unordered_map>
#include <exception>
#include <optional>

#include <SFML/Graphics.hpp>

namespace assets {
    class Tileset;
}

namespace game {

    enum ItemFamily {
        FOREST,
        FURNITURE,
    };

    enum ItemType {
        RAW_WOOD,
        PLANK,
        TABLE,
        CHAIR
    };

    struct ItemMeta {
        ItemType type; // unique id
        ItemFamily family;
        std::string name;
        std::string description;
        const assets::Tileset& iconsTileset;
        size_t iconsTileIndex;

        bool operator==(const ItemMeta& im) const  {
            return this->type == im.type;
        }

        bool operator!=(const ItemMeta& im) const  {
            return this->type != im.type;
        }
    };
    

    /**
     * Item
     */
    class Item {
    public:
        
        class MetaNotMatchException : std::runtime_error {
        public:
            MetaNotMatchException() : std::runtime_error("Items meta not the same!") {}
        };

        class CorruptionException : std::runtime_error {
        public:
            CorruptionException() : std::runtime_error("Items corrupted!") {}
        };

        class QuantityException : std::runtime_error {
        public:
            QuantityException() : std::runtime_error("Items quantity bad!") {}
        };

    private:
        friend class ItemsManager;
        Item(const ItemMeta& meta, int quantity = 1) : meta{&meta}, quantity{quantity} {}

    public:
        // Move constructor
        Item(Item&& other) noexcept
            : meta{other.meta}, quantity{other.quantity} {
            /* Make other corrupted */
            other.meta = nullptr;
            other.quantity = 0;
        }

        // Move assignment operator
        Item& operator=(Item&& other) noexcept {
            if (this != &other) {
                meta = other.meta;
                quantity = other.quantity;

                other.meta = nullptr;
                other.quantity = 0;
            }
            return *this;
        }

        // Deleted copy constructor and copy assignment to prevent copying
        Item(const Item&) = delete;
        Item& operator=(const Item&) = delete;

    public:
        Item operator+(Item&& other);

        Item operator-(Item&& other);

        Item& operator+=(Item&& other);

        Item& operator+=(int qty);

        Item& operator-=(Item&& other);
        
        Item& operator-=(int qty);

        bool operator>(const Item& other) const;
        
        bool operator>=(const Item& other) const;

        bool operator<(const Item& other) const;
        
        bool operator<=(const Item& other) const;

        bool operator==(const Item& other) const;
        
        bool operator!=(const Item& other) const;

        Item extract(int quantityToExtract);

        void setQuantity(int newQuantity) {
            if (newQuantity < 0) {
                throw QuantityException();
            }
            quantity = newQuantity;
        }

        int getQuantity() const {
            return quantity;
        }

        const ItemMeta* getMeta() const {
            return meta;
        }

        const bool isCorrupted() const {
            return !meta;
        }

    private:
        int quantity;

        const ItemMeta* meta;
    };


    /**
     * ItemsManager
     */
    class ItemsManager {
        ItemsManager();

        ItemsManager(const ItemsManager&) = delete;
        ItemsManager& operator=(const ItemsManager&) = delete;

        void addItemMeta(ItemType type, ItemFamily family, const std::string& name, const std::string& description, size_t tilesetIndex);

        std::unordered_map<ItemType, ItemMeta> itemMetas;

    public:
        static ItemsManager& get() {
            static ItemsManager instance;
            return instance;
        }

        Item createItem(ItemType type, int quantity = 1);

    };

}
