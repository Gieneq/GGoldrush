#include "Resourcer.hpp"

#include <iostream>

#include <game/items/Item.hpp>

namespace world {
    
    Resourcer::Resourcer(
        World& parentWorld, 
        Type type, 
        const sf::Vector2i& gridPosition, 
        const assets::Tileset& tileset, 
        size_t tileIndex, 
        game::ItemType resourceItemType,
        gfx::AnimatedSprite&& manualExtractionIcon
    ) : type{type}, 
        Structure(parentWorld, gridPosition, tileset, tileIndex), 
        resourceItemType{resourceItemType}, 
        manualExtractIcon{manualExtractionIcon} 
    {
        manualExtractIcon.setVisible(false);
        manualExtractIcon.setPosition(mainSprite.getPosition());
    }

    void Resourcer::tick() {
        if (extracting) {
            if (extractingCounter-- < 0) {
                /* Done - give item  */
                extracting = false;
                manualExtractIcon.setVisible(false);
                manualExtractIcon.stop();
                onManualExtract();
            }
        }

        manualExtractIcon.tick();
    }

    void Resourcer::draw(sf::RenderWindow& target) {
        Structure::draw(target);

        manualExtractIcon.draw(target);
    }

    void Resourcer::onManualExtract() {
        const auto& producedItemMeta = game::ItemsManager::get().findMeta(resourceItemType);
        std::cout << "Resourcer created 1 x " << producedItemMeta.name << std::endl;
        
        try {
            outputStyorage.add(game::ItemsManager::get().createItem(game::ItemType::RAW_WOOD, 1));
        } catch (const game::Storage::NoCapacityException&) {
            std::cout << "No more capacity" << std::endl;
            return;
        } catch (const game::Storage::NoSlotsException&) {
            std::cout << "No more slots" << std::endl;
            throw;
        } catch (const game::Item::CorruptionException&) {
            std::cout << "Corrupted" << std::endl;
            throw;
        }

        std::cout << "Added 1 x " << producedItemMeta.name << " to output storage, now overall items count=" << outputStyorage.getOverallItemsCount() << std::endl;

    }

    void Resourcer::onReleasedLMB() {
        Structure::onReleasedLMB();
        if (!extracting) {
            extractingCounter = 98;
            extracting = true;
            manualExtractIcon.setVisible(true);
            manualExtractIcon.start();
        }
    }

    void Resourcer::onReleasedRMB() {
        Structure::onReleasedRMB();

        
        std::cout << "Before: " << outputStyorage.toString() << std::endl;
        outputStyorage.moveAnyItemsTo(world.getPlayer().getStorage());
        std::cout << "After: " << outputStyorage.toString() << std::endl;
        std::cout << "Player: " << world.getPlayer().getStorage().toString() << std::endl;

        // std::vector<game::ItemType> itemsToProcess;
        // for (const auto& itemOccurance : outputStyorage) {
        //     itemsToProcess.push_back(itemOccurance.first);
        // }

        // for (const auto& itemType  : itemsToProcess) {
        //     const auto itemsCount = outputStyorage[itemType].getQuantity();

        //     try {
        //         outputStyorage.moveItemTo(itemType, world.getPlayer().getStorage());
        //     } catch (const game::Storage::NoCapacityException&) {
        //         std::cout << "Player has no free space" << std::endl;
        //         return;
        //     } catch (const game::Storage::NoSlotsException&) {
        //         std::cout << "Player has no free slots" << std::endl;
        //         return;
        //     }
            
        //     std::cout << "Player got " << itemsCount << " of " << game::ItemsManager::get().findMeta(itemType).name << std::endl;
        // }
    }

    std::string Resourcer::toString() const {
        return "Structure";
    }

    std::string Resourcer::getBrief() const {
        switch (type) {
        case Type::FOREST:
            return "Forest";
        
        case Type::MOUNTSIN:
            return "Mountains";

        default:
            return "Unknown";
        }
    }

}