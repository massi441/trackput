#pragma once

#ifdef _WIN32

#include "monitor/keyboard_monitor.hpp"
#include "singleton.hpp"
#include <windows.h>

namespace tckp::win {
    class KeyboardMonitor : public IKeyboardMonitor {
        SINGLETON(KeyboardMonitor)

    public:
        Result run() override;
        Result stop() override;
        
        Key getCurrentKey() override;

    private:
        HHOOK mHook;

        static LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM message, LPARAM keyboard);
    };
}

#endif
