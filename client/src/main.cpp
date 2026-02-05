#include <iostream>

#include "asio.hpp"
#include "nlohmann/json.hpp"

int main() {
    asio::io_context io;
    nlohmann::json j;

    j["Message"] = "Hello from the trackput client!";

    asio::post(io, [j] {
        std::cout << j["Message"] << std::endl;
    });

    io.run();

    return 0;
}
