#include <iostream>

#include "asio.hpp"
#include "nlohmann/json.hpp"

int main() {
    asio::io_context io;
    nlohmann::json j;

    j[1] = "JSON OBJECT";

    asio::post(io, [j]{
        std::cout << "Welcome To Trackput From Asio" << std::endl;
        std::cout << "This is the content of the json object: " << j[1] << std::endl;
    });

    io.run();

    return 0;
}
