#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>

#define INPUT_BUFFER_SIZE 1024

struct InputBuffer {
	unsigned char* data;
	size_t size;
	size_t pos;
};

struct InputBuffer* input_buffer_new(size_t size);
void input_buffer_destroy(struct InputBuffer* buffer);

void input_buffer_put_char(struct InputBuffer* buffer, char c);
void input_buffer_pop_char(struct InputBuffer* buffer);

#endif
