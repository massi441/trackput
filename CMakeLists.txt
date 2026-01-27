cmake_minimum_required(VERSION 3.15)
project(trackput)

set(CMAKE_CXX_STANDARD 17)

# Deps
include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-36-0
)

FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(asio)

# Output
add_executable(
    main
    src/main.cpp
)

target_include_directories(main PRIVATE ${asio_SOURCE_DIR}/asio/include)

target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)
