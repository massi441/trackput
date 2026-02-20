#pragma once

#include "monitor/keyboard_state.hpp"

namespace tckp {
    class KeyboardListener {
    public:
        void keyListener(const KeyboardState& state);
    };
}
