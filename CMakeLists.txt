cmake_minimum_required(VERSION 3.10)
project(SystemMonitor)

set(CMAKE_CXX_STANDARD 17)

# Find ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Your source files
add_executable(SystemMonitor
        src/main.cpp
        src/MonitorUI.cpp
)

# Link with ncurses
target_link_libraries(SystemMonitor ${CURSES_LIBRARIES})
