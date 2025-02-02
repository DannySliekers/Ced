#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminalutils.h"

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
        
        for (int i = 0; i < sizeof(lines[count]); i++) {
            if (lines[count][i] == NULL) {
                lines[count][i] = '\n';
                break;
            }
        }
        
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
            if (lines[count - 1][i] == '\n') {
                lines[count - 1][i] = c;
                lines[count - 1][i + 1] = '\n';
                break;
            }
        }

        clear_screen();
        for (int i = 0; i < count; i++) {
            printf("%i: ", i + 1);

            for (int j = 0; j < sizeof(lines[count]); j++) {
                printf("%c", lines[i][j]);
            }
        }
    }

    file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count;  i++) {
        for (int j = 0; j <= sizeof(lines[i]); j++) {
            if (lines[i][j] == '\n') {
                break;
            }

            fprintf(file, "%c", lines[i][j]);
        }
        
        fputc('\n', file);
    }

    fclose(file);
    clear_screen();
    return EXIT_SUCCESS;
}
