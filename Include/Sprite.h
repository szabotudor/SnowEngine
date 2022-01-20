#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<Vector.h>
#include<Utility.h>

using namespace std;

namespace ss {
	class Sprite {
		bool repeat = false;
		bool reverse = false;
		int frames, start = 0, end = 0;
		float time = 0.0f;
		double anim_time = 0.0;
		SDL_Window* window;
		SDL_Renderer* render;
		SDL_Surface* surface;
		SDL_Texture** textures;
		SDL_Rect* rects;
	public:
		int frame = 0;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		bool playing = false;
		Vector position;
		Sprite();
		Sprite(SDL_Window *window, const char* texture);
		Sprite(SDL_Window* window, int frames, const char ** textures);
		//Loads a new set of sprites, replacing the original textures
		void load(SDL_Window* window, int frames, const char** textures);
		//Draws the sprite on the window
		void draw(float delta);
		//Starts playing an animation from the start frame to the end frame at the given fps
		void play(int start, int end, int fps, bool repeat);
		//Plays the currently loaded animation from the set position
		void resume();
		//Stops the animation and resets it
		void stop();
		//Pauses the animation to be resumed by play
		void pause();
		//Returns the size of the sprite's texture in pixels
		Vector get_size();
	};
}
