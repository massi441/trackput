#pragma once 

#include "monitor/keyboard_monitor.hpp"
#include "monitor/mouse_monitor.hpp"

namespace tckp {
    class InputFactory {
    public:
        static IKeyboardMonitor& keyboardMonitor();
        static IMouseMonitor& mouseMonitor();
    };
}
