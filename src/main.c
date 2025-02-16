#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "fileutils.h"
#include "inputhandler.h"
#include "texteditor.h"

int main() {
    initscr(); // Start ncurses mode
    cbreak(); // Disable line buffering, but allow CTRL+C
    noecho(); // Don't show keypresses
    keypad(stdscr, TRUE); // interpret arrow and function keys

    FILE *file;
    file = fopen("example.txt", "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    SelectedText selected_text = {-1, -1, -1, -1};
    TextEditor text_editor = { {0}, 0, 0, 0,  selected_text};
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        strncpy(text_editor.lines[text_editor.line_number], line, sizeof(text_editor.lines[text_editor.line_number]) - 1);
        text_editor.lines[text_editor.line_number][sizeof(text_editor.lines[text_editor.line_number]) - 1] = '\0';
        text_editor.line_number++;
        text_editor.total_lines++;
    }

    fclose(file);
    set_cursor_pos(&text_editor);
    clear();
    print_to_screen(text_editor);
    move(text_editor.line_number - 1, text_editor.cursor_pos + get_line_number_skip(text_editor.line_number));        
    refresh();

    int c;
    while ((c = getch()) != 'q') {
        if (c != ERR) {
            handle_input(c, &text_editor);
            clear();
            print_to_screen(text_editor);
            move(text_editor.line_number - 1, text_editor.cursor_pos + + get_line_number_skip(text_editor.line_number));
            refresh();
        }
    }

    clear();
    endwin();
    int success = write_to_file(text_editor);
    return success;
}
