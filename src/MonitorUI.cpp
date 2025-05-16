//
// Created by Ronak on 16/05/25.
//

#include "../include/MonitorUI.h"
#include <ncurses.h>
#include <string>

void drawBar(int y, const std::string &label, float percent) {
    int width = COLS - 20;
    int filled = percent / 100.0 * width;
    mvprintw(y, 2, "%s [", label.c_str());
    attron(COLOR_PAIR(1));
    for (int i = 0; i < filled; i++) printw("|");
    attroff(COLOR_PAIR(1));
    for (int i = filled; i < width; i++) printw(" ");
    printw("] %.2f%%", percent);
}

void MonitorUI::refresh() {
    clear();
    float cpu = 30.0f; // Replace with real
    float mem = 45.5f; // Replace with real
    float swap = 2.1f; // Replace with real

    drawBar(1, "CPU", cpu);
    drawBar(2, "MEM", mem);
    drawBar(3, "SWAP", swap);

    mvprintw(5, 2, " PID   USER     CPU%%   MEM%%   TIME     COMMAND ");
    mvhline(6, 2, '-', COLS - 4);

    // Example static row
    mvprintw(7, 2, "1234  ronak     12.3    1.4    00:01:23 my_process");

    ::refresh(); // ✅ FIXED: call the ncurses refresh, not recursion
}
