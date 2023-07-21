#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "input.h"
#include "console.h"
#include "events.h"

#define MEASURE_INTERVAL_SECONDS 1

int main()
{
	struct ConsoleState* console = console_init();
	if(!console)
	{
		printf("Failed to initialize console");
		return 0;
	}

	int fps_counter = 0;
	double start_time, current_time;
	double fps;

	start_time = (double)clock() / CLOCKS_PER_SEC;

	while(!console->quit)
	{
		fps_counter++;
		poll_events(console);

		current_time = (double)clock() / CLOCKS_PER_SEC;
		
		if(current_time - start_time >= MEASURE_INTERVAL_SECONDS)
		{
			fps = (double)fps_counter / (current_time - start_time);
			printf("FPS: %f\n", fps);
			fps_counter = 0;
			start_time = current_time;
		}
	
		SDL_SetRenderDrawColor(console->renderer, 0, 0, 0, 0);
		SDL_RenderClear(console->renderer);
		
		SDL_Surface* input_surface = TTF_RenderText_Blended_Wrapped(console->font, (const char*)console->input_buffer->data, console->font_color, WINDOW_WIDTH);
		SDL_Texture* input_texture = SDL_CreateTextureFromSurface(console->renderer, input_surface);

		SDL_Rect input_rect = {0, 0, 0, 0};
		TTF_SizeText(console->font, (const char*)console->input_buffer->data, &input_rect.w, &input_rect.h);
		
		SDL_RenderCopy(console->renderer, input_texture, NULL, &input_rect);
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
