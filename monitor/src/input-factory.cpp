#include "monitor/input-factory.hpp"

#include "linux_mouse_monitor.hpp"
#include "macos_keyboard_monitor.hpp"
#include "windows_keyboard_monitor.hpp"

#include <stdexcept>

namespace tckp {
    IKeyboardMonitor& InputFactory::keyboardMonitor() {
        #ifdef _WIN32
            return tckp::win::KeyboardMonitor::Instance();
        #elifdef __APPLE__
            return new tckp::macos::KeyboardMonitor();
        #elifdef __linux__
            // linux
        #endif

        throw std::runtime_error("Unsupported platform");
    }

    IMouseMonitor& InputFactory::mouseMonitor() {

    }
}
