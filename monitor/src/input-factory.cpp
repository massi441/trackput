#include "monitor/input-factory.hpp"

#include "linux_mouse_monitor.hpp"
#include "macos_keyboard_monitor.hpp"
#include "windows_keyboard_monitor.hpp"

#include <stdexcept>

namespace tckp {
    IKeyboardMonitor& InputFactory::keyboardMonitor() {
        #if defined(_WIN32)
            return tckp::win::KeyboardMonitor::Instance();
        #elif defined(__APPLE__)
            return tckp::macos::KeyboardMonitor();
        #elif defined(__linux__)
            // linux
        #endif

        throw std::runtime_error("Unsupported platform");
    }

    IMouseMonitor& InputFactory::mouseMonitor() {
        throw std::runtime_error("Not implemented yet");
    }
}
