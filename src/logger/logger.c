#include <stdio.h>
#include "logger.h"

void debug_log(const char* message) {
    FILE *log_file;
    log_file = fopen("log.txt", "a");

    if (log_file == NULL) {
        perror("Error opening file");
    }

    fprintf(log_file, "DEBUG: %s \n", message);

    fclose(log_file);
}