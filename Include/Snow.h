#pragma once
#include<chrono>
#include<iostream>
#include<fstream>
#include<math.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<Utility.h>
#include<Vector.h>
#include<Collision.h>
#include<RandomNumberGenerator.h>
#include<Button.h>
#include<Particles.h>
#include<Texture.h>
#include<Sprite.h>
#include<Text.h>

using namespace std;

namespace ss {
	class Snow {
	public:
		Vector resolution;
		SDL_Event events[32];
		unsigned int target_fps = 60;
	private:
		double performace_frequency = (double)SDL_GetPerformanceFrequency();
		int max_events = 32;
		Vector sdl_window_size;
		SDL_Rect viewport;
		SDL_Window* window = NULL;
		SDL_Surface* surface = NULL;
		SDL_Renderer* render = NULL;
		int num_events = 0;
		unsigned int fps;
		Uint64 NOW = 0, LAST = 0;
		double delta_time, real_delta_time;
		float target_wait_time;
		bool _run = true;
		int numkeys;
		const Uint8* checkstate;
		
		bool previous_keystate[512] = {0};
		bool keystate[512] = {0};

		Uint32 previous_mousestate;
		Uint32 mousestate;
		int mpos_x, mpos_y;

		//Poll game events
		void poll_events();
		//Scale the window and center the renderer
		void scale_window(int w, int h);
	public:
		Snow(const char* name, Vector resolution = Vector(512, 288), Uint32 SDL_falgs = SDL_WINDOW_SHOWN, unsigned int framerate = 60);
		//Function to update the SDL2 components
		void update();
		//Function to clear the screen to a color
		void clear_screen(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
		//Returns the time since init
		long long get_time();
		//Returns the frames per second
		int get_fps();
		//Returns the mouse position
		Vector get_mouse_position();
		//Returns true if the given mouse button has been pressed
		bool is_button_pressed(Uint8 button);
		//Returns the SDL window (used especially for automatic texture scaling)
		SDL_Window* get_window();
		//Returns the SDL renderer (used when drawing or creating textures manually)
		SDL_Renderer* get_renderer();
		//Sets the window size to the given parameters (or resets the size if w and h are null)
		void resize_window(int w, int h);
		//Sets fullscreen mode to the given value
		void set_fullscreen(bool fs);
		//Returns true if the game window is in fullscreen mode
		bool get_fullscreen();
		//Returns true if the SDL_KeyScancode is pressed (eg: SDL_SCANCODE_RETURN)
		bool is_key_pressed(Uint8 key);
		//Returns true if the SDL_KeyScancode is just pressed this frame (eg: SDL_SCANCODE_RETURN)
		bool is_key_just_pressed(Uint8 key);
		//Returns true if the SDL_KeyScancode is just released this frame (eg: SDL_SCANCODE_RETURN)
		bool is_key_just_released(Uint8 key);
		//Checks if the engine is still running
		bool running(float &delta_time, float& real_delta_time);
		//Returns the number of events in the queue
		int get_num_events();
		//Stops all processes and background threads running in the helper library
		void quit();
	};
}
