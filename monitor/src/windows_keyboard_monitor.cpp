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

    LRESULT KeyboardMonitor::LowLevelKeyboardProc(int code, WPARAM messageId, LPARAM keyboardPtr) {
        if (code >= 0) {
            if (messageId == WM_KEYDOWN) {
                KBDLLHOOKSTRUCT* keyboard = (KBDLLHOOKSTRUCT*)keyboardPtr;
                std::string str = mapVkcToStr(keyboard->vkCode, keyboard->scanCode);
                std::cout << "Key Pressed: " << str << std::endl;
            }
        } else {
            std::cerr << "Something went wrong while processing the event" << std::endl;
        }

        return CallNextHookEx(KeyboardMonitor::Instance().mHook, code, messageId, keyboardPtr);
    }

    std::string KeyboardMonitor::mapVkcToStr(DWORD keyCode, DWORD scanCode) {
        BYTE keyboardState[256];
        if (!GetKeyboardState(keyboardState)) {
            return std::string();
        }

        constexpr int bufferSize = 4;
        WCHAR buffer[bufferSize];

        HKL layout = GetKeyboardLayout(0);

        int charCount = ToUnicodeEx(
            keyCode,
            scanCode,
            keyboardState,
            buffer,
            bufferSize,
            0,
            layout
        );

        // dead key
        if (charCount < 0) {
            return std::string();
        }

        // no available translation
        if (charCount == 0) {
            return std::string();
        }

        // TODO: Fix later
        std::wstring wstr(buffer, charCount);
        return std::string(wstr.begin(), wstr.end());
    }
}
