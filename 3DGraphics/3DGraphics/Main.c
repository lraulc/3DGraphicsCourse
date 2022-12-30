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
const int num_cube_points = 9;
vec3_t cube_points[N_POINTS(num_cube_points)]; // 9*9*9 cube
vec2_t projected_points[N_POINTS(num_cube_points)];

vec3_t camera_pos = {.x = 0, .y = 0, .z = -5};

float fov_factor = 640;

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

// Orthographic Projection
// Recieves 3D Vectors and converts to 2D
vec2_t project(vec3_t point)
{
	vec2_t projected_point = {
		.x = (fov_factor * point.x) / point.z,
		.y = (fov_factor * point.y) / point.z};
	return projected_point;
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
	for (int i = 0; i < N_POINTS(num_cube_points); i++)
	{
		vec3_t point = cube_points[i];

		// Move the camera position
		point.z -= camera_pos.z;

		// Project the current point
		vec2_t projected_point = project(point);

		// Save the projected to the 2D vector in the array of projected points
		projected_points[i] = projected_point;
	}
}

void render(void)
{
	//...
	draw_grid(0xFF222222); // Grid Color

	// Loop all projected points and render them
	for (int i = 0; i < N_POINTS(num_cube_points); i++)
	{
		vec2_t projected_point = projected_points[i];
		draw_rectangle(projected_point.x + window_width / 2, projected_point.y + window_height / 2, 4, 4, 0XFFFFAA00);
	}

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