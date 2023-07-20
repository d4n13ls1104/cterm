#include <string.h>

#include "input.h"

struct InputBuffer* input_buffer_new(size_t size) {
	struct InputBuffer* self = calloc(sizeof(struct InputBuffer), 1);
	if(!self) return NULL;

	self->data = calloc(size, 1);
	if(!self->data) {
		free(self);
		return NULL;
	}

	self->size = size;
	return self;
}

void input_buffer_destroy(struct InputBuffer* buffer) {
	if(!buffer) return;
	free(buffer->data);
	free(buffer);
}

bool input_buffer_put_char(struct InputBuffer* buffer, char* nbuf) {
	if(buffer->pos == buffer->size) return false; 

	buffer->data[buffer->pos] = *nbuf;
	buffer->pos++; 
	return true;
}

bool input_buffer_pop_char(struct InputBuffer* buffer) {
	if(buffer->pos == 0) return false;

	buffer->pos--;
	buffer->data[buffer->pos] = 0;
	return true;
}
