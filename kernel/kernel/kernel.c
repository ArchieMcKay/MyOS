#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialise();
	for (int i = 0; i < 100; i++)
		printf("Hello, kernel world!\n");
}
