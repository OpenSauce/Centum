#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

useconds_t character_display_delay = 25000;

char *get_input(int length) {
    char *input = (char *)malloc(length * sizeof(char));
    if (input == NULL) {
        printf("memory allocation failed!\n");
        exit(1);
    }
    
    if (fgets(input, length, stdin) == NULL) {
        printf("Error reading input.\n");
        free(input);
        exit(1);
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    return input;
}

void type(const char *format, ...) {
    char buffer[140];
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    const char *str = buffer;
    while (*str) {
        putchar(*str);
        fflush(stdout);
        usleep(character_display_delay);
        str++;
    }
}

void typeln(const char *format, ...) {
    type(format);
    putchar('\n');
}