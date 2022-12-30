#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;


// Pointer to first element of the array in the color buffer
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;


//Windo sizes
extern int window_width;
extern int window_height;


bool initialize_window(void);
void draw_grid(uint32_t gridColor);
void draw_pixel(int x, int y, uint32_t color);
void draw_rectangle(int x, int y, int width, int height, uint32_t rectColor);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void destroy_window(void);


#endif // !DISPLAY_H
