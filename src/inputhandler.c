#include <string.h>
#include <ncurses.h>
#include "inputhandler.h"
#include "texteditor.h"
#include "logger/logger.h"

static void insert_new_char(TextEditor* text_editor, char c) {
    char temp_lines[256];
    memcpy(temp_lines, text_editor->lines[text_editor->line_number - 1], sizeof(temp_lines));
    text_editor->lines[text_editor->line_number - 1][text_editor->cursor_pos] = c;
    
    for (int i = text_editor->cursor_pos; i < sizeof(text_editor->lines[text_editor->line_number - 1]) - 1; i++) {
        text_editor->lines[text_editor->line_number - 1][i + 1] = temp_lines[i];
    }

    text_editor->cursor_pos++;
}

void handle_input(int c, TextEditor* text_editor) {
    bool should_reset_selected_text = true;
    debug_log_int(c);
    if (c == KEY_BACKSPACE) {
        text_editor->lines[text_editor->line_number - 1][text_editor->cursor_pos - 1] = '\0';

        if (text_editor->cursor_pos > 0) {
            text_editor->cursor_pos--;
        }
    } else if (c == KEY_UP)  {
        if (text_editor->line_number - 1 > 0) {
            text_editor->line_number--;
        }
    } else if (c == KEY_DOWN)  {
        if (text_editor->line_number < text_editor->total_lines) {
            text_editor->line_number++;
        }
    } else if (c == KEY_RIGHT)  {
        int char_count = get_char_count(*text_editor);

        if (text_editor->cursor_pos < char_count) {
            text_editor->cursor_pos++;
        }
        else if (text_editor->line_number < text_editor->total_lines) {
            text_editor->line_number++;
            text_editor->cursor_pos = 0;
        }
    } else if (c == KEY_LEFT)  {
        if (text_editor->cursor_pos > 0) {
            text_editor->cursor_pos--;
        }
        else if(text_editor->line_number - 1 > 0) {
            text_editor->line_number--;

            int char_count = get_char_count(*text_editor);
            text_editor->cursor_pos = char_count;
        }
    } else if (c == KEY_SLEFT ) {
        should_reset_selected_text = false;
        bool is_set = is_selected_text_set(text_editor->selected_text);

        if (is_set) {
            text_editor->selected_text.begin_col--;
        } else {
            text_editor->selected_text.begin_col = text_editor->cursor_pos - 1;
            text_editor->selected_text.end_col = text_editor->cursor_pos - 1;
            text_editor->selected_text.begin_line = text_editor->line_number - 1;
            text_editor->selected_text.end_line = text_editor->line_number - 1;
        }

        text_editor->cursor_pos--;
    } else {
        insert_new_char(text_editor, c);
    }

    if (should_reset_selected_text) {
        reset_selected_text(&text_editor->selected_text);
    }

    if (c == KEY_ENTER) {
        text_editor->line_number++;
        text_editor->total_lines++;
        text_editor->cursor_pos = 0;
    }
}