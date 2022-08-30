#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This program needs to be compiled with an ix86-elf compiler"
#endif

enum vga_colour {
	VGA_COLOUR_BLACK = 0,
	VGA_COLOUR_BLUE= 1,
	VGA_COLOUR_GREEN = 2,
	VGA_COLOUR_CYAN = 3,
	VGA_COLOUR_RED = 4,
	VGA_COLOUR_MAGENTA = 5,
	VGA_COLOUR_BROWN = 6,
	VGA_COLOUR_LIGHT_GREY = 7,
	VGA_COLOUR_DARK_GREY = 8,
	VGA_COLOUR_LIGHT_BLUE = 9,
	VGA_COLOUR_LIGHT_GREEN = 10,
	VGA_COLOUR_LIGHT_CYAN = 11,
	VGA_COLOUR_LIGHT_RED = 12,
	VGA_COLOUR_LIGHT_MAGENTA = 13,
	VGA_COLOUR_LIGHT_BROWN = 14,
	VGA_COLOUR_WHITE = 15
};


static inline uint8_t vga_entry_colour(enum vga_colour fg, enum vga_colour bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t colour) {
	return (uint16_t) uc | (uint16_t) colour << 8;
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len]) {
		len++;
	}
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_colour;
uint16_t *terminal_buffer;

void terminal_initialise(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_colour = vga_entry_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t row = 0;  row < VGA_HEIGHT; row ++) {
		for (size_t column = 0; column < VGA_WIDTH; column++) {
			const size_t index = row * VGA_WIDTH + column;
			terminal_buffer[index] = vga_entry(' ', terminal_colour);
		}
	}
}

void terminal_setcolour(uint8_t colour) {
	terminal_colour = colour;
}

void terminal_putentryat(char c, uint8_t colour, size_t column, size_t row) {
	const size_t index = row * VGA_WIDTH + column;
	terminal_buffer[index] = vga_entry(c, colour);
}

void terminal_putchar(char c) {
	// TODO: Add newline support
	terminal_putentryat(c, terminal_colour, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	}
}

void terminal_write(const char *data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		terminal_putchar(data[i]);
	}
}

void terminal_writestring(const char *data) {
	terminal_write(data, strlen(data));
}

void terminal_scrollline(void) {
	// Memcpy buffer: rows [1, end] to rows[0, end - 1] and set row end to 0s
}

void kernel_main(void) {
	terminal_initialise();

	terminal_writestring("Hello, kernel world!\n");
}
