#pragma once

#include <iostream>
#include <unordered_map>

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
        int id;
        ItemFamily family;
        std::string name;
        std::string description;
        const assets::Tileset& iconsTileset; //FIXME
        size_t iconsTileIndex;
    };
    
    class Item {
        friend class ItemsManager;
        Item(const ItemMeta& meta, int quantity = 1) : meta{meta}, quantity{quantity} {}

    public:
        Item operator+(const Item& other) const;

        Item operator-(const Item& other) const;

        Item& operator+=(const Item& other);

        Item& operator-=(const Item& other);

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

        static int nextItemMetaId;

        Item createItem(ItemType type, int quantity = 1);

    };

}
