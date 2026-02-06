#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <iostream>

int mapKeyAction(CGEventType eventType) {
    if (eventType == kCGEventKeyDown) {
        return kUCKeyActionDown;
    }

    if (eventType == kCGEventKeyUp) {
        return kUCKeyActionUp;
    }

    return -1;
}

// 0b00000000000000000000001000000000

// Command, Shift, Options, Control, Capslock
UInt32 mapKeyModifiers(CGEventRef eventRef) {
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

CGEventRef keyboard_callback(CGEventTapProxy proxy, CGEventType eventType, CGEventRef eventRef, void* userData) {
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

    const UCKeyboardLayout* keyboardLayout = (const UCKeyboardLayout*)CFDataGetBytePtr(layoutData);

    // CGEventFlags eventFlags = CGEventGetFlags(eventRef);

    UInt32 modifierKeyState = mapKeyModifiers(eventRef); // Add mapper to properly convert

    std::cout << "Modifiers: " << modifierKeyState << std::endl;
    std::cout << "Modifiers (bits): 0b" << std::bitset<32>(modifierKeyState) << std::endl;

    UInt32 keyboardType = LMGetKbdType();
    OptionBits options = 0;
    UInt32 deadKeyState = 0;

    const UniCharCount bufferCount = 4;
    UniCharCount actualLength = 0;
    UniChar uniString[bufferCount];

    // CGEventSourceGetKeyboardType()

    // std::cout << "Event Type: " << eventType << std::endl;
    // std::cout << "Key Action: " << keyAction << std::endl;

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
        uniString
    );

    if (status != noErr) {
        const char* errorStr = GetMacOSStatusErrorString(status);
        std::cout << "An error occured while trying to translate key: " << errorStr << std::endl;
        return eventRef;
    }

    // const char* error = GetMacosS

    // std::cout << "Actual Length: " << actualLength << std::endl;
    // std::cout << "Key Code: " << keyCode << std::endl;

    // const unsigned char* str = 
    const char* keyStr = (const char*)(uniString); // FIX LATER;

    std::cout << "Key String: " << keyStr << std::endl;

    return eventRef;
}

int main() {
    CFMachPortRef tap = CGEventTapCreate(
        kCGSessionEventTap,
        kCGHeadInsertEventTap,
        kCGEventTapOptionListenOnly,
        CGEventMaskBit(kCGEventKeyDown),
        keyboard_callback,
        NULL
    );

    if (!tap) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    CFRunLoopSourceRef loopSourceRef = CFMachPortCreateRunLoopSource(NULL, tap, 0);

    CFRunLoopAddSource(CFRunLoopGetCurrent(), loopSourceRef, kCFRunLoopCommonModes);

    CGEventTapEnable(tap, true);

    std::cout << "Starting to listen for keys." << std::endl;

    CFRunLoopRun();

    return 0;
}