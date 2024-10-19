#include "Item.hpp"


#include "assets/AssetsManager.hpp"

namespace game {
    
    /**
     * Item related...
     */

    Item Item::extract(int quantityToExtract) {
        if (quantity < quantityToExtract) {
            throw QuantityException();
        }
        if (isCorrupted()) {
            throw CorruptionException();
        }
        quantity -= quantityToExtract;
        return Item(*meta, quantityToExtract);
    }

    Item Item::operator+(Item&& other) {
        if (meta != other.meta) {
            throw MetaNotMatchException();
        }
        if (isCorrupted() || other.isCorrupted()) {
            throw CorruptionException();
        }

        Item combinedItem(*meta, quantity + other.quantity);
        
        quantity = 0;
        meta = nullptr;

        other.quantity = 0;
        other.meta = nullptr;

        return combinedItem;
    }

Item Item::operator-(Item&& other) {
    if (meta != other.meta) {
        throw MetaNotMatchException();
    }
    if (quantity < other.quantity) {
        throw QuantityException();
    }
    if (isCorrupted() || other.isCorrupted()) {
        throw CorruptionException();
    }

    // Create the result item with the reduced quantity
    Item result(*meta, quantity - other.quantity);
    
    // Corrupt both items
    quantity = 0;
    meta = nullptr;

    other.quantity = 0;
    other.meta = nullptr;

    return result;
}

    Item& Item::operator+=(Item&& other) {
    if (meta != other.meta) {
        throw MetaNotMatchException();
    }
    if (isCorrupted() || other.isCorrupted()) {
        throw CorruptionException();
    }

    // Add the quantity from the other item
    quantity += other.quantity;

    // Corrupt the other item
    other.quantity = 0;
    other.meta = nullptr;

    return *this;
}

    Item& Item::operator+=(int qty) {
        if (this->quantity + qty < 0) {
            throw QuantityException();
        }
        
        this->quantity += qty;
        return *this;
    }

Item& Item::operator-=(Item&& other) {
    if (meta != other.meta) {
        throw MetaNotMatchException();
    }
    if (isCorrupted() || other.isCorrupted()) {
        throw CorruptionException();
    }
    if (quantity < other.quantity) {
        throw QuantityException();
    }

    // Subtract the quantity from the current item
    quantity -= other.quantity;

    // Corrupt the other item
    other.quantity = 0;
    other.meta = nullptr;

    return *this;
}
        
    Item& Item::operator-=(int qty) {
        if (this->quantity - qty < 0) {
            throw QuantityException();
        }
        
        this->quantity -= qty;
        return *this;
    }

    bool Item::operator>(const Item& other) const {
        if (meta != other.meta) {
            throw MetaNotMatchException();
        }
        if (isCorrupted()) {
            throw CorruptionException();
        }
        return this->quantity > other.quantity;
    }
    
    bool Item::operator>=(const Item& other) const {
        if (meta != other.meta) {
            throw MetaNotMatchException();
        }
        if (isCorrupted()) {
            throw CorruptionException();
        }
        return this->quantity >= other.quantity;
    }

    bool Item::operator<(const Item& other) const {
        if (meta != other.meta) {
            throw MetaNotMatchException();
        }
        if (isCorrupted()) {
            throw CorruptionException();
        }
        return this->quantity < other.quantity;
    }
    
    bool Item::operator<=(const Item& other) const {
        if (meta != other.meta) {
            throw MetaNotMatchException();
        }
        if (isCorrupted()) {
            throw CorruptionException();
        }
        return this->quantity <= other.quantity;
    }

    bool Item::operator==(const Item& other) const {
        if (meta != other.meta) {
            throw MetaNotMatchException();
        }
        if (isCorrupted()) {
            throw CorruptionException();
        }
        return this->quantity == other.quantity;
    }
    
    bool Item::operator!=(const Item& other) const {
        if (meta != other.meta) {
            throw MetaNotMatchException();
        }
        if (isCorrupted()) {
            throw CorruptionException();
        }
        return this->quantity != other.quantity;
    }


    /**
     * ItemsManager related...
     */

    ItemsManager::ItemsManager() {
        addItemMeta(ItemType::RAW_WOOD, ItemFamily::FOREST, "Raw Wood", "A piece of unprocessed wood.", 1);
        addItemMeta(ItemType::PLANK, ItemFamily::FOREST, "Wooden Plank", "A processed piece of wood.", 2);
        addItemMeta(ItemType::TABLE, ItemFamily::FURNITURE, "Wooden Table", "A sturdy wooden table.", 3);
        addItemMeta(ItemType::CHAIR, ItemFamily::FURNITURE, "Wooden Chair", "A comfortable wooden chair.", 4);
    }

    void ItemsManager::addItemMeta(ItemType type, ItemFamily family, const std::string& name, const std::string& description, size_t tilesetIndex) {
        itemMetas.insert({type, {type, family, name, description, 
            assets::AssetsManager::getInstane().getTileset(assets::AssetId::ITEMS), tilesetIndex}});
    }
    
    Item ItemsManager::createItem(ItemType type, int quantity) {
        auto it = itemMetas.find(type);
        if (it == itemMetas.end()) {
            throw std::invalid_argument("Invalid ItemType provided to createItem.");//TODO better exception
        }
        const ItemMeta& itemMeta = it->second;
        return Item(itemMeta, quantity);
    }

}