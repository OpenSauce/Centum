#ifndef UTIL_H
#define UTIL_H

typedef enum {
	COLOR_RESET,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_BLUE,
	COLOR_MAGENTA,
	COLOR_CYAN,
	COLOR_WHITE
} Color;

const char* get_color_code(Color color);
char* get_input_string(int length);
int get_input_int(int max);
void type_with_color(Color color, const char* format, ...);
void type(const char* str, ...);
void typeln(const char* str, ...);

#endif