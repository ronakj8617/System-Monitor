//
// Created by Ronak on 17/05/25.
//

#include "../include/ProcessParser.h"
#include "../include/ProcessInfo.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <pwd.h>
#include <vector>
#include <string>

namespace fs = std::filesystem;

std::string getUsername(uid_t uid) {
    struct passwd *pw = getpwuid(uid);
    return pw ? pw->pw_name : std::to_string(uid);
}

std::vector<ProcessInfo> getProcessList() {
    std::vector<ProcessInfo> processes;

    for (const auto &entry : fs::directory_iterator("/proc")) {
        std::string pidStr = entry.path().filename();
        if (!std::all_of(pidStr.begin(), pidStr.end(), ::isdigit)) continue;

        int pid = std::stoi(pidStr);
        std::ifstream status(entry.path() / "status");
        std::ifstream cmdline(entry.path() / "cmdline");

        if (!status || !cmdline) continue;

        uid_t uid = 0;
        std::string line;
        while (std::getline(status, line)) {
            if (line.rfind("Uid:", 0) == 0) {
                std::istringstream iss(line);
                std::string dummy;
                iss >> dummy >> uid;
                break;
            }
        }

        std::string command;
        std::getline(cmdline, command, '\0');
        if (command.empty()) command = "[" + pidStr + "]";

        ProcessInfo p;
        p.pid = pid;
        p.user = getUsername(uid);
        p.cpuUsage = 0.0f; // Optional: fill in using /proc/[pid]/stat
        p.memUsage = 0.0f; // Optional: fill in using /proc/[pid]/statm
        p.time = "00:00";  // Optional: parse time from stat
        p.command = command;

        processes.push_back(p);
    }

    return processes;
}
