#pragma once

#include "items/Storage.hpp"

namespace game {

    class Player {
    public:
        Player() {}

        Storage& getStorage() {
            return storage;
        }
        
    private:
        Storage storage;
    };

}