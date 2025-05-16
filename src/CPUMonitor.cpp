//
// Created by Ronak on 16/05/25.
//

#include "../include/CPUMonitor.h"
#include <fstream>
#include <sstream>
#include <string>
#include <thread>

float CPUMonitor::getCPUUsage() {
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);

    std::istringstream ss(line);
    std::string cpu;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    unsigned long long idleTime = idle + iowait;
    unsigned long long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;

    // On first call, we don't have previous readings
    if (lastTotalTime == 0) {
        lastIdleTime = idleTime;
        lastTotalTime = totalTime;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return getCPUUsage(); // re-run after 100ms delay
    }

    unsigned long long deltaTotal = totalTime - lastTotalTime;
    unsigned long long deltaIdle = idleTime - lastIdleTime;

    lastIdleTime = idleTime;
    lastTotalTime = totalTime;

    if (deltaTotal == 0) return 0.0f;
    return 100.0f * (1.0f - (float) deltaIdle / deltaTotal);
}
