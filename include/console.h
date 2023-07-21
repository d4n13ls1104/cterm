#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_TITLE "cterm"
#define FONT_PATH "/home/drew/repos/c/cterm/jb_mono.ttf"

#define WINDOW_WIDTH 	800
#define WINDOW_HEIGHT 	600

struct ConsoleState {
	SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* font;
	SDL_Color font_color;
	bool quit;

	struct InputBuffer* input_buffer;
};

struct ConsoleState* console_init();

#endif
