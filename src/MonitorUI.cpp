#include "../include/MonitorUI.h"
#include "../include/ProcessInfo.h" // define your struct here
#include <ncurses.h>
#include <string>
#include <vector>

extern std::vector<ProcessInfo> getProcessList(); // forward declaration

void drawBar(int y, const std::string &label, float percent) {
    int width = COLS - 20;
    int filled = percent / 100.0f * width;
    mvprintw(y, 2, "%s [", label.c_str());
    attron(COLOR_PAIR(1));
    for (int i = 0; i < filled; i++) printw("|");
    attroff(COLOR_PAIR(1));
    for (int i = filled; i < width; i++) printw(" ");
    printw("] %.2f%%", percent);
}

void MonitorUI::refresh() {
    clear();

    float cpu = 30.0f; // TODO: real CPU usage
    float mem = 45.5f; // TODO: real MEM usage
    float swap = 2.1f; // TODO: real SWAP usage

    drawBar(1, "CPU", cpu);
    drawBar(2, "MEM", mem);
    drawBar(3, "SWAP", swap);

    mvprintw(5, 2, " PID   USER     CPU%%   MEM%%   TIME     COMMAND ");
    mvhline(6, 2, '-', COLS - 4);

    std::vector<ProcessInfo> processes = getProcessList();
    int row = 7;
    for (const auto &p : processes) {
        mvprintw(row++, 2, "%5d %-8s %5.1f %6.1f %-8s %s",
                 p.pid, p.user.c_str(), p.cpuUsage, p.memUsage,
                 p.time.c_str(), p.command.c_str());
        if (row >= LINES - 1) break; // avoid overflow
    }

    ::refresh(); // flush ncurses buffer
}
