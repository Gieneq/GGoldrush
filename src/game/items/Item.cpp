#include "Item.hpp"


#include "assets/AssetsManager.hpp"

namespace game {

    Item Item::operator+(const Item& other) const {
        if (meta.id != other.meta.id) {  // Compare by unique id
            throw std::invalid_argument("Cannot add items of different types.");
        }
        return Item(meta, quantity + other.quantity);
    }

    Item Item::operator-(const Item& other) const {
        if (meta.id != other.meta.id) {  // Compare by unique id
            throw std::invalid_argument("Cannot subtract items of different types.");
        }
        if (quantity < other.quantity) {
            throw std::invalid_argument("Insufficient quantity to subtract.");
        }
        return Item(meta, quantity - other.quantity);
    }

    Item& Item::operator+=(const Item& other) {
        if (meta.id != other.meta.id) {  // Compare by unique id
            throw std::invalid_argument("Cannot add items of different types.");
        }
        quantity += other.quantity;
        return *this;
    }

    Item& Item::operator-=(const Item& other) {
        if (meta.id != other.meta.id) {  // Compare by unique id
            throw std::invalid_argument("Cannot subtract items of different types.");
        }
        if (quantity < other.quantity) {
            throw std::invalid_argument("Insufficient quantity to subtract.");
        }
        quantity -= other.quantity;
        return *this;
    }

    ItemsManager::ItemsManager() {
        addItemMeta(ItemType::RAW_WOOD, ItemFamily::FOREST, "Raw Wood", "A piece of unprocessed wood.", 1);
        addItemMeta(ItemType::PLANK, ItemFamily::FOREST, "Wooden Plank", "A processed piece of wood.", 2);
        addItemMeta(ItemType::TABLE, ItemFamily::FURNITURE, "Wooden Table", "A sturdy wooden table.", 3);
        addItemMeta(ItemType::CHAIR, ItemFamily::FURNITURE, "Wooden Chair", "A comfortable wooden chair.", 4);
    }

    void ItemsManager::addItemMeta(ItemType type, ItemFamily family, const std::string& name, const std::string& description, size_t tilesetIndex) {
        itemMetas.insert({type, {nextItemMetaId++, family, name, description, 
            assets::AssetsManager::getInstane().getTileset(assets::AssetId::ITEMS), tilesetIndex}});
    }

    int ItemsManager::nextItemMetaId{1};
    
    Item ItemsManager::createItem(ItemType type, int quantity) {
        auto it = itemMetas.find(type);
        if (it == itemMetas.end()) {
            throw std::invalid_argument("Invalid ItemType provided to createItem.");
        }

        return Item(it->second, quantity);
    }

}