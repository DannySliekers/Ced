#include "inputhandler.h"
#include "terminalutils.h"

#define BACKSPACE 127
#define LEFT_ARROW 68
#define NEW_LINE 10
#define ESCAPE 27
// Control Sequence Initiator
#define CSI 91
#define D 68

void handle_input(char c, int* line_number, int* cursor_pos, char lines[100][256]) {
    if (c == BACKSPACE) {
        lines[*line_number - 1][*cursor_pos - 1] = '\0';

        if (cursor_pos > 0) {
            (*cursor_pos)--;
        }
    }
    else if (c == 27 && getch() == CSI && getch() == D) {
        if (cursor_pos > 0) {
            (*cursor_pos)--;
        }
    }
    else {
        lines[*line_number - 1][*cursor_pos] = c;
        (*cursor_pos)++;
    }


    if (c == NEW_LINE) {
        (*line_number)++;
        *cursor_pos = 0;
    }
}