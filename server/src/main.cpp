#include <iostream>

#include "asio.hpp"
#include "nlohmann/json.hpp"
#include "monitor/test_monitor.h"

int main() {
    asio::io_context io;
    nlohmann::json j;

    j["Message"] = "Hello from the trackput server!";

    asio::post(io, [j] {
        std::cout << j["Message"] << std::endl; 
    });

    io.run();

    tckp::Monitor monitor;

    monitor.print();

    return 0;
}
