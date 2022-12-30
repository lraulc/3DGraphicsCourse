#include <stdio.h>	 // Adds standard library
#include <stdint.h>	 //Adds uninsigned ints for 8, 16 or 32
#include <stdbool.h> // Adds boolean support
#include <SDL2/SDL.h>
#include "Display.h"
#include "vector.h"

/////////////////////////////////////////////////////////
// Declare array of vectors
/////////////////////////////////////////////////////////

#define N_POINTS(x) (x * x * x)
vec3_t cube_points[N_POINTS(9)]; // 9*9*9 cube

bool is_running = false;

void setup(void)
{
	// Allocate color buffer in memory. //
	color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

	// Create SDL Texture used to display the color buffer
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height);
	if (!color_buffer)
	{
		fprintf(stderr, "Error allocating color buffer in memory.\n");
	}
	else
	{

		int point_count = 0;

		// Start loading array of vectors
		//  From -1 to 1 (in this 9x9x9 cube)
		for (float x = -1; x <= 1; x += 0.25)
		{
			for (float y = -1; y <= 1; y += 0.25)
			{
				for (float z = -1; z <= 1; z += 0.25)
				{
					vec3_t new_point = {.x = x, .y = y, .z = z};
					cube_points[point_count++] = new_point;
				}
			}
		}
	}
}

void process_input(void)
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			is_running = false;
		break;
	}
}

void update(void)
{
	// TODO:
}

void render(void)
{
	// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	//...
	draw_pixel(20, 20, 0XFFFFFF00);
	draw_rectangle((int)256, 256, 400, 400, 0XFFAA44AA);
	draw_grid(0xFF222222); // Grid Color

	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

int main(int argc, char *args[])
{
	is_running = initialize_window();

	setup();

	while (is_running)
	{
		process_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}