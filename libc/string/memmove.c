#include <string.h>

void *memmove(void *dest_ptr, const void *src_ptr, size_t size) {
	unsigned char *dst = (unsigned char *)dest_ptr;
	unsigned char *src = (unsigned char *)src_ptr;
	
	if (dst < src) {
		for (size_t i = 0; i < size; i++) {
			dst[i] = src[i];
		}
	} else {
		for (size_t i = size; i != 0; i--) {
			dst[i - 1] = src[i - 1];
		}
	}
	
	return dest_ptr;
}
