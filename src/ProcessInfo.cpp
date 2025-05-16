//
// Created by Ronak on 17/05/25.
//

#include "../include/ProcessInfo.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <pwd.h>

namespace fs = std::filesystem;

struct ProcessInfo {
    int pid;
    std::string user;
    float cpuUsage;
    float memUsage;
    std::string time;
    std::string command;
};

std::string getUsername(uid_t uid) {
    struct passwd *pw = getpwuid(uid);
    return pw ? pw->pw_name : std::to_string(uid);
}

std::vector<ProcessInfo> listProcesses() {
    std::vector<ProcessInfo> processes;

    for (const auto& entry : fs::directory_iterator("/proc")) {
        if (!entry.is_directory()) continue;
        std::string pidStr = entry.path().filename();
        if (!std::all_of(pidStr.begin(), pidStr.end(), ::isdigit)) continue;

        int pid = std::stoi(pidStr);
        std::ifstream statusFile(entry.path() / "status");
        std::ifstream cmdFile(entry.path() / "cmdline");
        std::ifstream statmFile(entry.path() / "statm");

        if (!statusFile || !cmdFile || !statmFile) continue;

        std::string line;
        uid_t uid = 0;
        while (std::getline(statusFile, line)) {
            if (line.rfind("Uid:", 0) == 0) {
                std::istringstream iss(line);
                std::string dummy;
                iss >> dummy >> uid;
                break;
            }
        }

        std::string user = getUsername(uid);
        std::string cmd;
        std::getline(cmdFile, cmd, '\0');
        if (cmd.empty()) cmd = "[" + pidStr + "]";

        // Fake CPU/MEM data for now
        processes.push_back({pid, user, 0.0, 0.0, "00:00", cmd});
    }

    return processes;
}
