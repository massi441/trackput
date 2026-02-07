#include "monitor/input-factory.hpp"

#include "linux_mouse_monitor.hpp"
#include "macos_keyboard_monitor.hpp"
#include "windows_keyboard_monitor.hpp"

namespace tckp {
    IKeyboardMonitor* InputFactory::keyboardMonitor() {
        #if defined (_WIN32)
            // return new tckp:
        #elif defined(__APPLE__)
            return new tckp::macos::KeyboardMonitor();
        #elif defined(__linux__)
            // linux
        #endif

        return nullptr;
    }

    IMouseMonitor* InputFactory::mouseMonitor() {

    }
}
