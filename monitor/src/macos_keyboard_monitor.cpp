#include "macos_keyboard_monitor.hpp"

#include <Carbon/Carbon.h>
#include <iostream>

namespace tckp::macos {
    Result KeyboardMonitor::run() {
        mTap = CGEventTapCreate(
            kCGSessionEventTap,
            kCGHeadInsertEventTap,
            kCGEventTapOptionListenOnly,
            CGEventMaskBit(kCGEventKeyDown),
            callback,
            this
        );

        if (!mTap) {
            return Result::MISSING_PRIVILLEGES;
        }

        mLoopSourceRef = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, mTap, 0);
        mRunLoopRef = CFRunLoopGetCurrent();

        CFRunLoopAddSource(mRunLoopRef, mLoopSourceRef, kCFRunLoopCommonModes);

        CGEventTapEnable(mTap, true);

        CFRunLoopRun();

        CFRunLoopRemoveSource(mRunLoopRef, mLoopSourceRef, kCFRunLoopCommonModes);

        CFRelease(mLoopSourceRef);

        CFRelease(mTap);

        return Result::SUCCESS;
    }

    Result KeyboardMonitor::stop() {
        if (mRunLoopRef) {
            CFRunLoopStop(mRunLoopRef);
            return Result::SUCCESS;
        }

        return Result::FAILURE;
    }

    Key KeyboardMonitor::getCurrentKey() {
        return Key::A;
    }

    CGEventRef KeyboardMonitor::callback(CGEventTapProxy proxy, CGEventType eventType, CGEventRef eventRef, void *userData) {
        CGKeyCode keyCode = (CGKeyCode)(CGEventGetIntegerValueField(eventRef, kCGKeyboardEventKeycode));

        int keyAction = mapKeyAction(eventType);

        if (keyAction == -1) {
            std::cout << "CG event '" << eventType << "' not supported, aborting" << std::endl;
            return eventRef;
        }

        TISInputSourceRef keyboardRef = TISCopyCurrentKeyboardInputSource();

        CFDataRef layoutData = (CFDataRef)TISGetInputSourceProperty(keyboardRef, kTISPropertyUnicodeKeyLayoutData);

        if (!layoutData) {
            std::cerr << "No keyboard layout data found" << std::endl;
            return eventRef;
        }

        const UCKeyboardLayout *keyboardLayout = (const UCKeyboardLayout *)CFDataGetBytePtr(layoutData);

        UInt32 modifierKeyState = mapKeyModifiers(eventRef);

        // std::cout << "Modifiers: " << modifierKeyState << std::endl;
        // std::cout << "Modifiers (bits): 0b" << std::bitset<32>(modifierKeyState) << std::endl;

        UInt32 keyboardType = LMGetKbdType();
        OptionBits options = 0;
        UInt32 deadKeyState = 0;

        const UniCharCount bufferCount = 4;
        UniCharCount actualLength = 0;
        UniChar uniString[bufferCount];

        OSStatus status = UCKeyTranslate(
            keyboardLayout,
            keyCode,
            keyAction,
            modifierKeyState,
            keyboardType,
            options,
            &deadKeyState,
            bufferCount,
            &actualLength,
            uniString);

        if (status != noErr)
        {
            const char *errorStr = GetMacOSStatusErrorString(status);
            std::cout << "An error occured while trying to translate key: " << errorStr << std::endl;
            return eventRef;
        }

        const char *keyStr = (const char* )(uniString); // FIX LATER;

        std::cout << "Key String: " << keyStr << std::endl;

        return eventRef;
    }

    int KeyboardMonitor::mapKeyAction(CGEventType eventType) {
        if (eventType == kCGEventKeyDown) {
            return kUCKeyActionDown;
        }

        if (eventType == kCGEventKeyUp) {
            return kUCKeyActionUp;
        }

        return -1;
    }

    UInt32 KeyboardMonitor::mapKeyModifiers(CGEventRef eventRef) {
        CGEventFlags flags = CGEventGetFlags(eventRef);

        UInt32 cfMask = 0;

        int modifierShift = 8;

        if ((flags & kCGEventFlagMaskCommand) != 0) {
            cfMask |= (cmdKey >> modifierShift);
        }

        if ((flags & kCGEventFlagMaskShift) != 0) {
            cfMask |= (shiftKey) >> modifierShift;
        }

        if ((flags & kCGEventFlagMaskAlternate) != 0) {
            cfMask |= (optionKey) >> modifierShift;
        }

        if ((flags & kCGEventFlagMaskControl) != 0) {
            cfMask |= (controlKey >> modifierShift);
        }

        if ((flags & kCGEventFlagMaskAlphaShift) != 0) {
            cfMask |= (alphaLock >> modifierShift);
        }

        return cfMask;
    }
}
