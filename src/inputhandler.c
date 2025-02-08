#include "inputhandler.h"
#include "terminalutils.h"
#include "texteditor.h"

#define BACKSPACE 127
#define LEFT_ARROW 68
#define NEW_LINE 10
#define ESCAPE 27
// Control Sequence Initiator
#define CSI 91
#define D 68

void handle_input(char c, TextEditor* text_editor) {
    if (c == BACKSPACE) {
        text_editor->lines[text_editor->line_number - 1][text_editor->cursor_pos - 1] = '\0';

        if (text_editor->cursor_pos > 0) {
            text_editor->cursor_pos--;
        }
    }
    else if (c == 27 && getch() == CSI && getch() == D) {
        if (text_editor->cursor_pos > 0) {
            text_editor->cursor_pos--;
        }
    }
    else {
        text_editor->lines[text_editor->line_number - 1][text_editor->cursor_pos] = c;
        text_editor->cursor_pos++;
    }


    if (c == NEW_LINE) {
        text_editor->line_number++;
        text_editor->cursor_pos = 0;
    }
}