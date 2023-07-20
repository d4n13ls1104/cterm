#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "input.h"
#include "console.h"
#include "events.h"

int main() {
	struct ConsoleState* console = console_init();
	if(!console) {
		printf("Failed to initialize console");
		return 0;
	}

	while(!console->quit) {
		poll_events(console);
	
		SDL_SetRenderDrawColor(console->renderer, 0, 0, 0, 0);
		SDL_RenderClear(console->renderer);
		
		SDL_Surface* input_surface = TTF_RenderText_Solid(console->font, (const char*)console->input_buffer->data, console->font_color);
		SDL_Texture* input_texture = SDL_CreateTextureFromSurface(console->renderer, input_surface);
		
		TTF_SizeText(console->font, (const char*)console->input_buffer->data, &console->linesize.w, &console->linesize.h);
		
		SDL_RenderCopy(console->renderer, input_texture, NULL, &console->linesize);
		SDL_RenderPresent(console->renderer);
		
		SDL_DestroyTexture(input_texture);
		SDL_FreeSurface(input_surface);
	}
	
	TTF_Quit();
	SDL_DestroyRenderer(console->renderer);
	SDL_DestroyWindow(console->window);
	SDL_Quit();
	
	return 0;
}
