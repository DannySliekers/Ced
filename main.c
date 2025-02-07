#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminalutils.h"
#include "fileutils.h"

int main() {
    FILE *file;

    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char lines[100][256];
    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        strncpy(lines[count], line, sizeof(lines[count]) - 1);
        lines[count][sizeof(lines[count]) - 1] = '\0';
        count++;
    }

    fclose(file);
    clear_screen();

    for (int i = 0; i < count; i++) {
        printf("%i: ", i + 1);

        for (int j = 0; j < sizeof(lines[i]); j++) {
            printf("%c", lines[i][j]);
        }
    }

    char c;
    while ((c = getch()) != 'q') {
        for (int i = 0; i < sizeof(lines[count - 1]); i++) {
            if (lines[count - 1][i] == '\0') {
                lines[count - 1][i] = c;
                break;
            }
        }

        if (c == 10) {
            count++;
        }

        clear_screen();

        for (int i = 0; i < count; i++) {
            printf("%i: ", i + 1);

            for (int j = 0; j < sizeof(lines[count]); j++) {
                printf("%c", lines[i][j]);
            }
        }
    }

    int success = write_to_file(lines, count);

    clear_screen();
    return success;
}
