//
// Created by Ronak on 16/05/25.
//

#include "../include/CPUMonitor.h"
#include <fstream>
#include <sstream>
#include <string>

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

    float usage = 0.0f;
    if (lastTotalTime != 0) {
        usage = 100.0f * (1.0f - (float)(idleTime - lastIdleTime) / (totalTime - lastTotalTime));
    }

    lastIdleTime = idleTime;
    lastTotalTime = totalTime;

    return usage;
}
