#include <stdlib.h>
#include <stdio.h>
#include "fileutils.h"
#include "texteditor.h"

int write_to_file(TextEditor text_editor) {
    FILE *file;
    file = fopen("example.txt", "w");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }


    for (int i = 0; i < text_editor.total_lines;  i++) {
        for (int j = 0; j <= sizeof(text_editor.lines[i]); j++) {
            if (text_editor.lines[i][j] == '\0') {
                break;
            }

            fprintf(file, "%c", text_editor.lines[i][j]);
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}