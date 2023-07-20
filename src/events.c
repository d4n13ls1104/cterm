#include "events.h"
#include "input.h"

#include <SDL2/SDL.h>

void poll_events(struct ConsoleState* console) {
	SDL_Event e;
	while(SDL_PollEvent(&e))  {
		switch(e.type) {
			case SDL_QUIT: console->quit = true; break;

			case SDL_TEXTINPUT:
				input_buffer_put_char(console->input_buffer, e.text.text);
				break;

			case SDL_KEYDOWN:
				if(e.key.keysym.sym == SDLK_BACKSPACE) input_buffer_pop_char(console->input_buffer);
			break;
		}
	}

}
