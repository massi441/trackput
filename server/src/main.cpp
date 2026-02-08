#include <iostream>

#include "monitor/input-factory.hpp"

int main() {
    try {
        tckp::IKeyboardMonitor& monitor = tckp::InputFactory::keyboardMonitor();
        std::cout << "Starting Monitor" << std::endl;
        monitor.run();
    } catch (const std::runtime_error& error) {
        std::cout << error.what() << std::endl;
        return 1;
    }
    return 0;
}
