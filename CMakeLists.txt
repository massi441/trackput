cmake_minimum_required(VERSION 3.15)
project(trackput VERSION 1.0.0)

# Cpp stuff
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Deps
find_package(nlohmann_json CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)

# Building
option(BUILD_SERVER "Enable building the server" ON)
option(BUILD_CLIENT "Enable building the client" ON)
option(BUILD_TEST "Enable building the tests" OFF)

if (BUILD_SERVER)
    add_subdirectory(server)
endif()

if (BUILD_CLIENT)
    add_subdirectory(client)
endif()

if (BUILD_TEST)
    enable_testing()
    add_subdirectory(tests)
endif()

if (BUILD_SERVER OR BUILD_CLIENT OR BUILD_TEST)
    add_subdirectory(monitor)
endif()
