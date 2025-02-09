#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

typedef struct {
    char lines[100][256];
    int line_number;
    int cursor_pos;
    int total_lines;
} TextEditor;

void print_to_screen(TextEditor text_editor);
void set_cursor_pos(TextEditor* text_editor);
int get_char_count(TextEditor text_editor);

#endif