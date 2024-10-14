#pragma once

#include "items/Storage.hpp"

namespace game {

    class Player {
    public:
        Player() {}
        
    private:
        SlotsLimitedStorage storage;
    };

}