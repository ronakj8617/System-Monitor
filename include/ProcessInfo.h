//
// Created by Ronak on 17/05/25.
//

#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include <string>

struct ProcessInfo {
    int pid;
    std::string user;
    float cpuUsage;
    float memUsage;
    std::string time;
    std::string command;
};

#endif
