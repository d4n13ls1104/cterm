#include <stdbool.h>
#include <stdlib.h>
#include "input.h"
#include "console.h"

SDL_Window* initialize_window()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Could not be initialized.\n"
		       "SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN);
	if(!window)
	{
		printf("Window couldn't be initialized.\n"
		       "SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}

	return window;
}

TTF_Font* initialize_font()
{
	if(TTF_Init() < 0)
	{
		printf("TTF Could not be initialized.\n"
		       "TTF_ Error: %s\n", TTF_GetError());
		return NULL;
	}

	TTF_Font* font = TTF_OpenFont(FONT_PATH, 16);
	if(!font)
	{
		printf("Font failed to load.\n"
		       "TTF_Error: %s\n", TTF_GetError());
		return NULL;
	}

	return font;

}

SDL_Renderer* initialize_renderer(struct SDL_Window* window)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
			SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		printf("Renderer could not be initialized.\n"
		       "SDL_Error: %s\n", SDL_GetError());
		return NULL;
	} 
	return renderer;
}

struct ConsoleState* console_init() {
	struct ConsoleState* self = calloc(sizeof(struct ConsoleState), 1);
	if(!self) return NULL;

	SDL_Window* window = initialize_window();
	if(!window)
	{
		SDL_Quit();
		free(self);
		return NULL;
	}

	TTF_Font* font = initialize_font();
	if(!font)
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		free(self);
		return NULL;
	}

	SDL_Renderer* renderer = initialize_renderer(window);
	if(!renderer)
	{
		TTF_Quit();
		SDL_DestroyWindow(window);
		SDL_Quit();
		free(self);
		return NULL;
	}

	SDL_Color font_color = {255, 255, 255, 255};

	struct InputBuffer* input_buffer = input_buffer_new(INPUT_BUFFER_SIZE);
	if(!input_buffer)
	{
		TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		free(self);
		return NULL;
	}

	char* terminal_prefix = "[drew@cterm]$ ";
	for(size_t i = 0; i < 14; i++) input_buffer_put_char(input_buffer, &terminal_prefix[i]);

	self->input_buffer = input_buffer;
	self->window = window;
	self->renderer = renderer;
	self->font = font;
	self->font_color = font_color;
	self->quit = false;

	return self;
}
