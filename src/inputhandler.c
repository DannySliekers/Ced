#include <string.h>
#include "inputhandler.h"
#include "terminalutils.h"
#include "texteditor.h"

#define BACKSPACE 127
#define LEFT_ARROW 68
#define NEW_LINE 10
#define ESCAPE 27
// Control Sequence Initiator
#define CSI 91
#define A 65
#define B 66
#define C 67
#define D 68

static void handle_esc(TextEditor* text_editor) {
    char potential_csi = getch();

    if (potential_csi == CSI) {
        char potential_cs = getch();

        //Up arrow key
        if (potential_cs == A) {
            if (text_editor->line_number - 1 > 0) {
                text_editor->line_number--;
            }
        }
        //Down arrow key
        else if (potential_cs == B) {
            if (text_editor->line_number < text_editor->total_lines) {
                text_editor->line_number++;
            }
        }
        // Right arrow key
        else if (potential_cs == C) {
            int char_count = get_char_count(*text_editor);

            if (text_editor->cursor_pos < char_count) {
                text_editor->cursor_pos++;
            }
            else if (text_editor->line_number < text_editor->total_lines) {
                text_editor->line_number++;
                text_editor->cursor_pos = 0;
            }
        }
        //Left arrow key
        else if (potential_cs == D) {
            if (text_editor->cursor_pos > 0) {
                text_editor->cursor_pos--;
            }
            else if(text_editor->line_number - 1 > 0) {
                text_editor->line_number--;

                int char_count = get_char_count(*text_editor);
                text_editor->cursor_pos = char_count;
            }
        }
    }
}

static void insert_new_char(TextEditor* text_editor, char c) {
    char temp_lines[256];
    memcpy(temp_lines, text_editor->lines[text_editor->line_number - 1], sizeof(temp_lines));
    text_editor->lines[text_editor->line_number - 1][text_editor->cursor_pos] = c;
    
    for (int i = text_editor->cursor_pos; i < sizeof(text_editor->lines[text_editor->line_number - 1]) - 1; i++) {
        text_editor->lines[text_editor->line_number - 1][i + 1] = temp_lines[i];
    }

    text_editor->cursor_pos++;
}

void handle_input(char c, TextEditor* text_editor) {
    if (c == BACKSPACE) {
        text_editor->lines[text_editor->line_number - 1][text_editor->cursor_pos - 1] = '\0';

        if (text_editor->cursor_pos > 0) {
            text_editor->cursor_pos--;
        }
    }
    else if (c == 27 ) {
        handle_esc(text_editor);
    } else {
        insert_new_char(text_editor, c);
    }

    if (c == NEW_LINE) {
        text_editor->line_number++;
        text_editor->total_lines++;
        text_editor->cursor_pos = 0;
    }
}