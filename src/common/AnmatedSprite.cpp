#include "AnimatedSprite.hpp"

#include "assets/AssetsManager.hpp"

namespace gfx {

    AnimatedSprite::AnimatedSprite(
        const assets::Tileset& tileset, 
        std::pair<size_t, size_t> tilesetIndicesRange, 
        int durationTicks
    ) : tileset{tileset}, tilesetIndicesRange{tilesetIndicesRange}, currentFrameIndex{tilesetIndicesRange.first},
    intervalNextFrameTicks(durationTicks / (tilesetIndicesRange.second - tilesetIndicesRange.first + 1)) {
        if (tilesetIndicesRange.first >= tilesetIndicesRange.second) {
            throw std::invalid_argument("Invalid tilesetIndicesRange: second value should be greater than or equal to first.");
        }

        sprite.setTexture(tileset.getTexture());
        sprite.setOrigin({0,0});
        sprite.setPosition({0,0});
        updateSpriteFrame();
    }

    
    void AnimatedSprite::updateSpriteFrame() {
        sprite.setTextureRect(tileset.getTileRectByIndex(currentFrameIndex));
    }

}