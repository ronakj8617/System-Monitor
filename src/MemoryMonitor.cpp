//
// Created by Ronak on 16/05/25.
//

#include "MemoryMonitor.h"
#include <fstream>
#include <sstream>
#include <string>

float getMemoryUsagePercent() {
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) return 0.0f;

    std::string line;
    long total = 0, free = 0, buffers = 0, cached = 0;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string key;
        long value;
        std::string unit;
        ss >> key >> value >> unit;

        if (key == "MemTotal:") total = value;
        else if (key == "MemFree:") free = value;
        else if (key == "Buffers:") buffers = value;
        else if (key == "Cached:") cached = value;

        if (total && free && buffers && cached) break;
    }

    if (total == 0) return 0.0f;

    long used = total - free - buffers - cached;
    return static_cast<float>(used) / total * 100.0f;
}
