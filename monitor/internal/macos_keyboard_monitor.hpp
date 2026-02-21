#pragma once

#ifdef __APPLE__

#include <ApplicationServices/ApplicationServices.h>
#include "monitor/keyboard_monitor.hpp"
#include "singleton.hpp"

namespace tckp::macos {
    class KeyboardMonitor : public IKeyboardMonitor {
        SINGLETON(KeyboardMonitor)
    public:
        // Have custom event
        Result run() override;
        Result stop() override;

        Key getCurrentKey() override;
        
    private:
        CFMachPortRef mTap = nullptr;
        CFRunLoopSourceRef mLoopSourceRef = nullptr;
        CFRunLoopRef mRunLoopRef = nullptr;

        static int mapKeyAction(CGEventType eventType);
        static UInt32 mapKeyModifiers(CGEventRef eventRef);

        static CGEventRef callback(CGEventTapProxy proxy, CGEventType eventType, CGEventRef eventRef, void *userData);
    };
}

#endif
