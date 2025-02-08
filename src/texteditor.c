#include <stdio.h>
#include "texteditor.h"

void print_to_screen(TextEditor text_editor) {
    for (int i = 0; i < text_editor.line_number; i++) {
        printf("%i: ", i + 1);

        for (int j = 0; j < sizeof(text_editor.lines[i]); j++) {
            printf("%c", text_editor.lines[i][j]);
        }
    }
}

void set_cursor_pos(TextEditor* text_editor) {
    for (int i = 0; i < sizeof(text_editor->lines[text_editor->line_number]); i++){
        if (text_editor->lines[text_editor->line_number - 1][i] == '\0') {
            text_editor->cursor_pos = i;
            break;
        }
    }
}