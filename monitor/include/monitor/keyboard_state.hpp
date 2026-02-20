#pragma once

#include <cstdint>
#include "monitor/key.hpp"

namespace tckp {
    class KeyboardState {
    public:
        KeyboardState();

        bool isKeyDown(Key key);
        bool isKeyUp(Key key);

        bool isShift() const;
        bool isControl() const;
        bool isCapsLock() const;
        bool isAlt() const;

    private:
        int8_t mModifiers;
    };
}
