#include <stdio.h>
#include <stdint.h> //Adds uninsigned ints for 8, 16 or 32
#include <stdbool.h>
#include <SDL.h>


bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


// Pointer to first element of the array in the color buffer
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;


//Windo sizes
int window_width;
int window_height;

bool initialize_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}
	// Use SDL to query what is the fullscreen max width and height
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	// --> SET WINDOW Sizes based on the main monitor
	window_width = display_mode.w;
	window_height = display_mode.h;

	// Create SDL Window
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		fprintf(stderr, "Error creating SDL Window.\n");
		return false;
	}

	// Create SDL Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer. \n");
		return false;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}


void setup(void)
{
	// Allocate color buffer in memory. //
	color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

	// Create SDL Texture used to display the color buffer
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
	if (!color_buffer)
	{
		fprintf(stderr, "Error allocating color buffer in memory.\n");
	}
	else {

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
	//TODO:

}

void draw_grid(uint32_t gridColor)
{
	// Encontrar multiplos de 10 de X y de Y
	int steps = 10;

	// Vertical Lines
	for (int y = 0; y < window_height; y+= 10)
	{
		for (int x = 0; x < window_width; x+= 10)
		{
			color_buffer[(window_width * y) + x] = gridColor;
		}
	}
}


void draw_rectangle(int x, int y, int width, int height, uint32_t rectColor)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int current_x = x + i;
			int current_y = y + j;
			color_buffer[(window_width * current_x) + current_y] = rectColor;
		}
	}
}

void render_color_buffer(void)
{
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(window_width * sizeof(uint32_t))
	);

	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color)
{
	for (int y = 0; y < window_height; y++)
	{
		for (int x = 0; x < window_width; x++)
		{
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

void render(void)
{
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);


	//...
	draw_rectangle((int)256, 256, 400, 400, 0XFFFFFFFF);
	draw_grid(0xFF222222); // Grid Color


	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

void destroy_window(void)
{
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


int main(int argc, char* args[])
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