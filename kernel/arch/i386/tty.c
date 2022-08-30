#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_colour;
static uint16_t *terminal_buffer;

void terminal_initialise(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_colour = vga_entry_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t row_i = 0; row_i < VGA_HEIGHT; row_i++) {
		for (size_t col_i = 0; col_i < VGA_WIDTH; col_i++) {
			const size_t index = row_i * VGA_WIDTH + col_i;
			terminal_buffer[index] = vga_entry(' ', terminal_colour);
		}
	}
}

void terminal_setcolour(uint8_t colour) {
	terminal_colour = colour;
}

void terminal_putentryat(unsigned char c, uint8_t colour, size_t col_i, size_t row_i) {
	const size_t index = row_i * VGA_WIDTH + col_i;
	terminal_buffer[index] = vga_entry(c, colour);
}

void terminal_scroll(int line) {
	// char c;

	// for (size_t loop = line * (vga_width * 2) + 0xb80000; loop < vga_width * 2; loop++) {
	// 	const char c = *loop;
	// 	*(loop - (vga_width * 2)) = c;
	// }
}

void terminal_delete_last_line(void) {
	// int x;
	// int *ptr;

	// for (
}

void terminal_putchar(char c) {
	if (c == '\n') {
		terminal_putentryat(' ', terminal_colour, terminal_column, terminal_row);
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	} else {
		terminal_putentryat(c, terminal_colour, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = 0;
			}
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
