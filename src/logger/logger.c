#include <stdio.h>
#include <stdbool.h>
#include "logger.h"

void debug_log_string(const char* message) {
    FILE *log_file;
    log_file = fopen("log.txt", "a");

    if (log_file == NULL) {
        perror("Error opening file");
    }

    fprintf(log_file, "DEBUG: %s \n", message);

    fclose(log_file);
}

void debug_log_int(const int number) {
    FILE *log_file;
    log_file = fopen("log.txt", "a");

    if (log_file == NULL) {
        perror("Error opening file");
    }

    fprintf(log_file, "DEBUG: %i \n", number);

    fclose(log_file);
}

void debug_log_char_codes(const char* message) {
    FILE *log_file;
    log_file = fopen("log.txt", "a");

    if (log_file == NULL) {
        perror("Error opening file");
    }

    for (int i = 0; i < sizeof(message); i++) {
        fprintf(log_file, "DEBUG: %i \n", message[i]);
    }

    fclose(log_file);
}

void debug_log_bool(const bool boolean) {
    FILE *log_file;
    log_file = fopen("log.txt", "a");

    if (log_file == NULL) {
        perror("Error opening file");
    }

    fprintf(log_file, "DEBUG: %s \n", boolean ? "true" : "false");

    fclose(log_file);
}