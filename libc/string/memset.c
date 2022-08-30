#include <string.h>

void *memset(void *buff_ptr, int value, size_t size) {
	unsigned char *buff = (unsigned char *) buff_ptr;

	for (size_t i = 0; i < size; i++) {
		buff[i] = value;
	}

	return buff_ptr;
}
