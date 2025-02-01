#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "terminalutils.h"

void clear_screen() {
    // \033[H will position the cursor to the home position 
    // and \033[J stands for erase lines below.
    printf("\033[H\033[J");
}

void enable_raw_mode() {
    struct termios term;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &term);

    // Modify the terminal attributes for raw mode
    term.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    term.c_cc[VMIN] = 1;             // Minimum number of characters to read
    term.c_cc[VTIME] = 0;            // No timeout

    // Apply the new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void disable_raw_mode() {
    struct termios term;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &term);

    // Restore canonical mode and echo
    term.c_lflag |= (ICANON | ECHO);

    // Apply the restored settings
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char getch() {
    enable_raw_mode();
    char c = getchar();
    disable_raw_mode();
    return c;
}