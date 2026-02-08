#pragma once

#ifdef _WIN32

#include "monitor/keyboard_monitor.hpp"
#include "singleton.hpp"
#include <string>
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

        static LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM messageId, LPARAM keyboardPtr);
        static std::string mapVkcToStr(DWORD virtualCode, DWORD scanCode);
    };
}

#endif
