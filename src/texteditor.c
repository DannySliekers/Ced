#include <stdio.h>
#include <math.h>
#include <ncurses.h>
#include "texteditor.h"

void print_to_screen(TextEditor text_editor) {
    for (int i = 0; i < text_editor.total_lines; i++) {
        printw("%i: ", i + 1);
        
        if (i == text_editor.selected_text.begin_line) {
            for (int j = 0; j < sizeof(text_editor.lines[i]); j++) {
                if (j >= text_editor.selected_text.begin_col && j <= text_editor.selected_text.end_col) {
                    // Highlights the selected text
                    printw("\033[97;44m%c\033[0m", text_editor.lines[i][j]);
                }
                else {
                    printw("%c", text_editor.lines[i][j]);
                }
            }
        }
        else {
            printw("%s", text_editor.lines[i]);
        }
    }
}

void set_cursor_pos(TextEditor* text_editor) {
    for (int i = 0; i < sizeof(text_editor->lines[text_editor->total_lines]); i++){
        if (text_editor->lines[text_editor->line_number - 1][i] == '\0') {
            text_editor->cursor_pos = i;
            break;
        }
    }
}

int get_char_count(TextEditor text_editor) {
    for (int i = 0; i < sizeof(text_editor.lines[text_editor.line_number - 1 ]); i++) {
        if (text_editor.lines[text_editor.line_number - 1][i] == '\0' 
            || text_editor.lines[text_editor.line_number - 1][i] == '\n') {
            return i;
        }
    }

    return -1;
}

int get_line_number_skip(int line_number) {
    return 4 + (int)log10(line_number);
}
