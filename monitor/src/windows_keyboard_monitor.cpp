#include "windows_keyboard_monitor.hpp"

#include <iostream>

namespace tckp::win {
    Result KeyboardMonitor::run() {
        mHook = SetWindowsHookEx(WH_KEYBOARD_LL, &LowLevelKeyboardProc, GetModuleHandle(NULL), 0);

        if (mHook == NULL) {
            std::cerr << "An error occured while trying to install the hook" << std::endl;
            DWORD error = GetLastError();

            std::cout << error << std::endl;

            return Result::FAILURE;
        }

        MSG message;
        BOOL result;

        while ((result = GetMessage(&message, NULL, 0, 0) != 0)) {
            if (result == -1) {
                DWORD error = GetLastError();
                std::cerr << "An error occured while receiving the message: " << error << std::endl;
            }

            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        std::cout << "Starting Keyboard Monitor" << std::endl;
        return Result::SUCCESS;
    }

    Result KeyboardMonitor::stop() {
        if (UnhookWindowsHookEx(mHook)) {
            std::cout << "Stopped Windows Monitor" << std::endl;
            return Result::SUCCESS;
        } else {
            std::cerr << "An error occured while trying to stop the monitor" << std::endl;
            return Result::FAILURE;
        }
    }

    Key KeyboardMonitor::getCurrentKey() {
        return Key::A;
    }

    LRESULT KeyboardMonitor::LowLevelKeyboardProc(int code, WPARAM message, LPARAM keyboard) {
        if (code >= 0) {
            if (message == WM_KEYDOWN) {
                std::cout << "Key Pressed!" << std::endl;
            }

        } else {
            std::cerr << "Something went wrong while processing the event" << std::endl;
        }

        return CallNextHookEx(KeyboardMonitor::Instance().mHook, code, message, keyboard);
    }
}
