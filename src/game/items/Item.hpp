#pragma once

#include <iostream>
#include <unordered_map>
#include <exception>

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
        const assets::Tileset& iconsTileset; //FIXME
        size_t iconsTileIndex;

        bool operator==(const ItemMeta& im) const  {
            return this->type == im.type;
        }

        bool operator!=(const ItemMeta& im) const  {
            return this->type != im.type;
        }
    };
    
    class Item {
    public:
        
        class ItemsNotMatchException : std::runtime_error {
        public:
            ItemsNotMatchException() : std::runtime_error("Items meta not the same!") {}
        };

        class ItemsQuantityException : std::runtime_error {
        public:
            ItemsQuantityException() : std::runtime_error("Items quantity bad!") {}
        };

    private:
        friend class ItemsManager;
        Item(const ItemMeta& meta, int quantity = 1) : meta{meta}, quantity{quantity} {}

        void checkMetaEqual(const Item& other) const {
            if (this->meta != meta) {
                throw ItemsNotMatchException();
            }
        }
        
        void checkMetaEqual(const Item& other) {
            if (this->meta != meta) {
                throw ItemsNotMatchException();
            }
        }

    public:
        Item operator+(const Item& other) const;

        Item operator-(const Item& other) const;

        Item& operator+=(const Item& other);

        Item& operator-=(const Item& other);

        Item& operator+=(int qty);
        
        Item& operator-=(int qty);

        bool operator>(const Item& other) const;
        
        bool operator>=(const Item& other) const;

        bool operator<(const Item& other) const;
        
        bool operator<=(const Item& other) const;

        bool operator==(const Item& other) const;
        
        bool operator!=(const Item& other) const;


        void setQuantity(int newQuantity) {
            if (newQuantity < 0) {
                throw ItemsQuantityException();
            }
            quantity = newQuantity;
        }

        int getQuantity() const {
            return quantity;
        }

        const ItemMeta& meta;

    private:
        int quantity;
    };

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
