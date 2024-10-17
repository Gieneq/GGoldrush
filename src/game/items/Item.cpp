#include "Item.hpp"


#include "assets/AssetsManager.hpp"

namespace game {

    Item Item::operator+(const Item& other) const {
        checkMetaEqual(other);
        return Item(meta, quantity + other.quantity);
    }

    Item Item::operator-(const Item& other) const {
        checkMetaEqual(other);
        if (quantity < other.quantity) {
            throw ItemsQuantityException();
        }
        return Item(meta, quantity - other.quantity);
    }

    Item& Item::operator+=(const Item& other) {
        return operator+=(other.quantity);
    }

    Item& Item::operator-=(const Item& other) {
        return operator-=(other.quantity);
    }

    Item& Item::operator+=(int qty) {
        if (this->quantity + qty < 0) {
            throw ItemsQuantityException();
        }
        
        this->quantity += qty;
        return *this;
    }
        
    Item& Item::operator-=(int qty) {
        if (this->quantity - qty < 0) {
            throw ItemsQuantityException();
        }
        
        this->quantity -= qty;
        return *this;
    }

    bool Item::operator>(const Item& other) const {
        checkMetaEqual(other);
        return this->quantity > other.quantity;
    }
    
    bool Item::operator>=(const Item& other) const {
        checkMetaEqual(other);
        return this->quantity >= other.quantity;
    }

    bool Item::operator<(const Item& other) const {
        checkMetaEqual(other);
        return this->quantity < other.quantity;
    }
    
    bool Item::operator<=(const Item& other) const {
        checkMetaEqual(other);
        return this->quantity <= other.quantity;
    }

    bool Item::operator==(const Item& other) const {
        checkMetaEqual(other);
        return this->quantity == other.quantity;
    }
    
    bool Item::operator!=(const Item& other) const {
        checkMetaEqual(other);
        return this->quantity != other.quantity;
    }


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

    // int ItemsManager::nextItemMetaId{1};
    
    Item ItemsManager::createItem(ItemType type, int quantity) {
        auto it = itemMetas.find(type);
        if (it == itemMetas.end()) {
            throw std::invalid_argument("Invalid ItemType provided to createItem.");//TODO better exception
        }

        return Item(it->second, quantity);
    }

}