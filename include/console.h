#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct ConsoleState {
	SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* font;
	SDL_Color font_color;
	SDL_Rect linesize;
	bool quit;

	struct InputBuffer* input_buffer;
};

struct ConsoleState* console_init();

#endif
