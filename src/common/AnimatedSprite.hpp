#pragma once

#include <utility>
#include <exception>

#include <SFML/Graphics.hpp>

namespace assets {
    class Tileset;
}

namespace gfx {

    class AnimatedSprite {
    public:
        AnimatedSprite(const assets::Tileset& tileset, std::pair<size_t, size_t> tilesetIndicesRange, int durationTicks = 100);

        void setVisible(bool visibility) {
            this->visible = visibility;
        }

        void setPosition(const sf::Vector2f& position) {
            sprite.setPosition(position);
        }

        void start() {
            recentFrameTimeTicks = 0;
            running = true;
        }

        void stop() {
            running = false;
        }

        bool isVisible() const {
            return visible;
        }

        void tick() {
            if (running) {
                recentFrameTimeTicks++;

                // Check if it's time to switch to the next frame
                if (recentFrameTimeTicks >= intervalNextFrameTicks) {
                    recentFrameTimeTicks = 0; // Reset frame time counter

                    // Calculate the next frame index
                    currentFrameIndex++;
                    if (currentFrameIndex > tilesetIndicesRange.second) {
                        currentFrameIndex = tilesetIndicesRange.first; // Loop back to the first frame
                    }

                    // Set the sprite's texture rect based on the current frame
                    updateSpriteFrame();
                }
            }
        }

        void draw(sf::RenderWindow& target) {
            if (visible) {
                target.draw(sprite);
            }
        }

        void updateSpriteFrame();

    private:
        bool visible{true};
        bool running{true};
        int recentFrameTimeTicks{0};
        int intervalNextFrameTicks;
        size_t currentFrameIndex;
        const assets::Tileset& tileset;
        std::pair<size_t, size_t> tilesetIndicesRange;
        sf::Sprite sprite;
    };

}