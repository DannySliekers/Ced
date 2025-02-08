#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminalutils.h"
#include "fileutils.h"
#include "inputhandler.h"

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
        
        handle_input(c, &line_number, &cursor_pos, lines);
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
