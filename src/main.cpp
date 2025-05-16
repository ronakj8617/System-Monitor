// main.cpp
#include <ncurses.h>
#include <unistd.h>
#include "../include/MonitorUI.h"

int main() {
    initscr();              // Start ncurses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo input
    curs_set(0);            // Hide cursor
    nodelay(stdscr, TRUE);  // Non-blocking input
    keypad(stdscr, TRUE);   // Enable arrow keys

    MonitorUI ui;
    while (true) {
        int ch = getch();
        if (ch == 'q') break;

        ui.refresh();
        usleep(500000); // Refresh every 500ms
    }

    endwin();
    return 0;
}
