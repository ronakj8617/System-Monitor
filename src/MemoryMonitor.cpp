//
// Created by Ronak on 16/05/25.
//

#include "MemoryMonitor.h"
#include <fstream>
#include <string>

float getMemoryUsagePercent() {
    std::ifstream file("/proc/meminfo");
    std::string label;
    long total = 0, free = 0, buffers = 0, cached = 0, value;

    while (file >> label >> value) {
        if (label == "MemTotal:") total = value;
        else if (label == "MemFree:") free = value;
        else if (label == "Buffers:") buffers = value;
        else if (label == "Cached:") cached = value;
        if (total && free && buffers && cached) break;
    }

    long used = total - free - buffers - cached;
    return (float)used / total * 100.0f;
}
