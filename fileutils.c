#include <stdlib.h>
#include <stdio.h>
#include "fileutils.h"

int write_to_file(char lines[100][256], int count) {
    FILE *file;
    file = fopen("example.txt", "w");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }


    for (int i = 0; i < count;  i++) {
        for (int j = 0; j <= sizeof(lines[i]); j++) {
            if (lines[i][j] == '\0') {
                break;
            }

            fprintf(file, "%c", lines[i][j]);
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}