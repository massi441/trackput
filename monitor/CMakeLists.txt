add_library(
    monitor
    src/macos/macos_keyboard_monitor.cpp
    src/input-factory.cpp
)

target_include_directories(monitor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(monitor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/internal")

if (APPLE)
    target_link_libraries(server PRIVATE "-framework ApplicationServices")
    target_link_libraries(server PRIVATE "-framework Carbon")
endif()
