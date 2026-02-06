add_library(
    monitor
    src/test-monitor.cpp
)

target_include_directories(monitor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
