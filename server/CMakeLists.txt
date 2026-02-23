add_executable(
    server 
    src/main.cpp
)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(server PRIVATE monitor)
target_link_libraries(server PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(server PRIVATE asio::asio)
