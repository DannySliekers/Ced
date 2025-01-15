#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < sizeof(lines[i]); j++) {
            printf("%c", lines[i][j]);
        }
    }

    char c = getchar();
    printf("You entered: %c", c);

    fclose(file);

    return EXIT_SUCCESS;
}