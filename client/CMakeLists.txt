add_executable(
    client
    src/main.cpp
)

target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(client PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(client PRIVATE ${asio_SOURCE_DIR}/asio/include)
