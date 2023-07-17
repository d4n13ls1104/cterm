#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "input.h"

#define SCREEN_WIDTH 	800
#define SCREEN_HEIGHT 	600

int main() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Could not be initialized.\n"
				"SDL_Error: %s\n", SDL_GetError());
		return 0;
	}
	if(TTF_Init() < 0) {
		printf("TTF Could not be initialized.\n"
				"TTF_Error: %s\n", TTF_GetError());
	}

	SDL_Window* window = SDL_CreateWindow("dterm",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if(!window) {
		printf("Window couldn't be initialized.\n"
				"SDL_Error: %s\n", SDL_GetError());
	} else {
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		if(!renderer) {
			printf("Renderer could not be initialized.\n"
					"SDL_Error: %s\n", SDL_GetError());
		} else {
			TTF_Font* font = TTF_OpenFont("jb_mono.ttf", 24);
			if(!font) {
				printf("Font failed to load. TTF_Error: %s\n", TTF_GetError());
				return 0;
			}
			SDL_Color font_color = {0xFF, 0xFF, 0xFF, 0xFF};


			SDL_Rect input_rect;
			input_rect.x = 0;
			input_rect.y = 0;
			input_rect.w = 800;
			input_rect.h = 100;

			struct InputBuffer* input_buffer = input_buffer_new(INPUT_BUFFER_SIZE);

			bool quit = false;
			while(!quit) {
				SDL_Event e;
				while(SDL_PollEvent(&e)) {
					switch(e.type) {
						case SDL_QUIT: quit = true; break;

						case SDL_TEXTINPUT:
							input_buffer_push_char(input_buffer, e.text.text);
						break;

						case SDL_KEYDOWN:
							if(e.key.keysym.sym == SDLK_BACKSPACE) input_buffer_pop_char(input_buffer);
						break;
					}
				}

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				SDL_RenderClear(renderer);

				SDL_Surface* input_surface = TTF_RenderText_Solid(font, (const char*)input_buffer->data, font_color);
				SDL_Texture* input_texture = SDL_CreateTextureFromSurface(renderer, input_surface);

				SDL_RenderCopy(renderer, input_texture, NULL, &input_rect);
				SDL_RenderPresent(renderer);

				SDL_FreeSurface(input_surface);
				SDL_DestroyTexture(input_texture);
			}
			TTF_Quit();

			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
	}
	return 0;
}
