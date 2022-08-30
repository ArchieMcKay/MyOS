#include <string.h>

void *memcpy(void *restrict dest_ptr, const void *restrict src_ptr, size_t size) {
	unsigned char *dest = (unsigned char *) dest_ptr;
	unsigned char *src = (unsigned char *) src_ptr;

	for (size_t i = 0; i < size; i++) {
		dest[i] = src[i];
	}

	return dest_ptr;
}
