//
// Created by Ronak on 16/05/25.
//

#pragma once

class CPUMonitor {
public:
    float getCPUUsage();
private:
    unsigned long long lastIdleTime = 0;
    unsigned long long lastTotalTime = 0;
};
