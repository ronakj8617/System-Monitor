cmake_minimum_required(VERSION 3.10)

project(SystemMonitor)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(SystemMonitor ${SOURCES}
        src/CPUMonitor.cpp
        include/CPUMonitor.h
        src/MemoryMonitor.cpp
        include/MemoryMonitor.h
        src/MonitorUI.cpp
        include/MonitorUI.h)