//
// Created by Ronak on 16/05/25.
//
#include <iostream>
#include <thread>
#include <chrono>
#include "CPUMonitor.h"
#include "MemoryMonitor.h"

int main() {
    CPUMonitor cpu;
    while (true) {
        float cpuUsage = cpu.getCPUUsage();
        float memUsage = getMemoryUsagePercent();

        system("clear");
        std::cout << "[CPU]    " << cpuUsage << "%    [Memory]  " << memUsage << "%\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
