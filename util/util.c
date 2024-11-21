#include "util.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

useconds_t character_display_delay = 20000;

const char* get_color_code(Color color)
{
	switch (color) {
	case COLOR_RED:
		return "\033[31m";
	case COLOR_GREEN:
		return "\033[32m";
	case COLOR_YELLOW:
		return "\033[33m";
	case COLOR_BLUE:
		return "\033[34m";
	case COLOR_MAGENTA:
		return "\033[35m";
	case COLOR_CYAN:
		return "\033[36m";
	case COLOR_WHITE:
		return "\033[37m";
	case COLOR_RESET:
	default:
		return "\033[0m";
	}
}

char* get_input_string(int length)
{
	char* input = (char*)malloc(length * sizeof(char));
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

int get_input_int(int max)
{
	int input = -1;
	int valid = false;

	while (!valid) {
		type("Enter a number (1-%d): ", max);
		if (scanf("%d", &input) == 1) {
			if (input >= 1 && input <= max) {
				valid = true;
			}
		} else {
			while (getchar() != '\n')
				;
		}
	}

	return input;
}
void type(const char* format, ...)
{
	char buffer[140];
	va_list args;

	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	const char* str = buffer;
	while (*str) {
		putchar(*str);
		fflush(stdout);
		usleep(character_display_delay);
		str++;
	}
}

void type_with_color(Color color, const char* format, ...)
{
	va_list args;
	va_start(args, format);

	char buffer[140];
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	printf("%s", get_color_code(color));
	type("%s", buffer);
	printf("%s", get_color_code(COLOR_RESET));
}

void typeln(const char* format, ...)
{
	type(format);
	putchar('\n');
}