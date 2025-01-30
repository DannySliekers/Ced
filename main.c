#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>


void enable_raw_mode() {
    struct termios term;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &term);

    // Modify the terminal attributes for raw mode
    term.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    term.c_cc[VMIN] = 1;             // Minimum number of characters to read
    term.c_cc[VTIME] = 0;            // No timeout

    // Apply the new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void disable_raw_mode() {
    struct termios term;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &term);

    // Restore canonical mode and echo
    term.c_lflag |= (ICANON | ECHO);

    // Apply the restored settings
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char getch() {
    enable_raw_mode();
    char c = getchar();
    disable_raw_mode();
    return c;
}

int main() {
    FILE *file;

    file = fopen("example.txt", "r+");
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

    char c;
    while ((c = getch()) != 'q') {
        fprintf(file, &c);
        printf("You entered: %c", c);
    }

    fclose(file);

    return EXIT_SUCCESS;
}
