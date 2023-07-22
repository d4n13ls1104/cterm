#include <string.h>
#include "input.h"

struct InputBuffer* input_buffer_new(size_t size)
{
	struct InputBuffer* self = calloc(sizeof(struct InputBuffer), 1);
	if(!self) return NULL;

	self->data = calloc(size, 1);
	if(!self->data)
	{
		free(self);
		return NULL;
	}

	self->size = size;
	return self;
}

void input_buffer_destroy(struct InputBuffer* buffer)
{
	if(!buffer) return;
	free(buffer->data);
	free(buffer);
}

void input_buffer_put_char(struct InputBuffer* buffer, char c)
{
	if(buffer->pos == buffer->size) return; 
	buffer->data[buffer->pos] = c;
	buffer->pos++; 
}

void input_buffer_pop_char(struct InputBuffer* buffer)
{
	if(buffer->pos == 0) return;
	buffer->pos--;
	buffer->data[buffer->pos] = 0;
}
