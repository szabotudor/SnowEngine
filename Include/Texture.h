#pragma once
#include<iostream>
#include<Vector.h>
#include<SDL.h>
#include<SDL_image.h>

using namespace std;


namespace ss {
	class Texture {
		SDL_Window* window;
		SDL_Renderer* render;
		SDL_Texture* texture = nullptr;
		SDL_PixelFormat* format;
		Uint32* pixels = nullptr;
		Vector resolution;
	public:
		SDL_Rect clip_rect;
		Vector position;
		Vector scale;
		//Creates a texture from a file
		Texture(SDL_Window* window, const char* texture);
		//Creates an empty texture of a certain size
		Texture(SDL_Window* window, Vector size = Vector(32));
		//Draws the texture to the window
		void draw();
		//Updates the texture
		void update();
		//Sets the color of a certain pixel (only applies when update is called)
		void set_pixel(Vector pixel, int r, int g, int b, int a = 255);
		//Sets the color of a certain pixel (only applies when update is called)
		void set_pixel(Vector pixel, SDL_Color color);
	};
}
