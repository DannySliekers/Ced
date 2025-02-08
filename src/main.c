#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminalutils.h"
#include "fileutils.h"

#define BACKSPACE 127
#define LEFT_ARROW 68
#define NEW_LINE 10
#define ESCAPE 27
// Control Sequence Initiator
#define CSI 91
#define D 68

int main() {
    FILE *file;

    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char lines[100][256];
    char line[256];
    int line_number = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        strncpy(lines[line_number], line, sizeof(lines[line_number]) - 1);
        lines[line_number][sizeof(lines[line_number]) - 1] = '\0';
        line_number++;
    }

    fclose(file);
    clear_screen();

    for (int i = 0; i < line_number; i++) {
        printf("%i: ", i + 1);

        for (int j = 0; j < sizeof(lines[i]); j++) {
            printf("%c", lines[i][j]);
        }
    }

    char c;
    int cursor_pos = 0;
    while ((c = getch()) != 'q') {
        
        if (c == BACKSPACE) {
            lines[line_number - 1][cursor_pos - 1] = '\0';

            if (cursor_pos > 0) {
                cursor_pos--;
            }
        }
        else if (c == 27 && getch() == CSI && getch() == D) {
            if (cursor_pos > 0) {
                cursor_pos--;
            }
        }
        else {
            lines[line_number - 1][cursor_pos] = c;
            cursor_pos++;
        }


        if (c == NEW_LINE) {
            line_number++;
            cursor_pos = 0;
        }

        clear_screen();

        for (int i = 0; i < line_number; i++) {
            printf("%i: ", i + 1);

            for (int j = 0; j < sizeof(lines[line_number]); j++) {
                printf("%c", lines[i][j]);
            }
        }

        //Move cursor
        printf("\033[%i;%iH", line_number, cursor_pos + 4);
    }


    int success = write_to_file(lines, line_number);

    clear_screen();
    return success;
}
