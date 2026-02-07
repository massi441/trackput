#include <iostream>

#include "monitor/input-factory.hpp"

int main() {
    tckp::IKeyboardMonitor* monitor = tckp::InputFactory::keyboardMonitor();

    monitor->run();

    std::cout << "Stopped Monitoring" << std::endl;

    delete monitor;

    return 0;
}
