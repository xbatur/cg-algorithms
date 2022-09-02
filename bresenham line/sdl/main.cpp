#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "geo_elements.h"
#include <iostream>
int main() {
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;
	bool quit = false;
	int x0, y0, x1, y1;
	int count = 0;
	bool lineDraw = false;
	bool lineMode = false;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(1920, 1080, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_l:
					lineMode = !lineMode;
					//std::cout << "Line mode: " << lineMode << "\n";
					break;
				}
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button) {
				case SDL_BUTTON_LEFT:
					if (lineMode) {
						if (count > 0) {
							SDL_GetMouseState(&x1, &y1);
							//std::cout << "Mouse pressed for end point.\n";
							count = 0;
							lineDraw = true;
						}
						if (count <= 0 && !lineDraw) {
							SDL_GetMouseState(&x0, &y0);
							//std::cout << "Mouse pressed for start point.\n";
							count++;
						}	
					}	
					break;
				}
			}
		}
		if (lineDraw) {
			lineDraw = false;
			Line2D line(x0, y0, x1, y1);
			line.drawLine(renderer);
		}
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}