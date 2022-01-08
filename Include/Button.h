#pragma once
#include<string.h>

using namespace std;


namespace ss {
	class Button {
	public:
		enum class Type {
			Press,
			Toggle
		};
		enum class BackgroundType {
			Rect,
			Empty,
			Texture
		};
		enum class State {
			OFF,
			ON
		};
		SDL_Rect viewport;
		Uint8 font_size;
		State state = State::OFF;
		Vector position;
		bool disabled = false;
		bool hovered = false;
		bool pressed = false;
		bool held = false;
		bool just_pressed = false;
		bool just_released = false;

	private:
		int border = 0;
		Type type = Type::Press;
		BackgroundType background_type = BackgroundType::Rect;
		string text;
		SDL_Color text_color, border_color, fill_color;
		TTF_Font* font;
		SDL_Surface* surface;
		SDL_Texture* texture;
		SDL_Renderer* render;
		SDL_Window* window;
		SDL_Rect rect, border_rect;

	public:
		Button(SDL_Window* window, const char* text = "Button", const char* font = "basic.ttf", unsigned int font_size = 18);
		Button(SDL_Window* window, SDL_Color bgd_color, SDL_Color border_color, SDL_Color text_color, unsigned int border_thickness, const char* text, const char* font = "basic.ttf", unsigned int font_size = 18);
		Button(SDL_Window* window, SDL_Color text_color, const char* text, const char* font = "basic.ttf", unsigned int font_size = 18);
		//Button(Type type = Type::Press, const char* text = "Button", const char* font = "Pixel.ttf", BackgroundType background_type = BackgroundType::Rect);

		//Sets the button text to the given parameter
		void set_text(char* text);
		//Returns the text set on the button
		string get_text();
		//Loads specified font and uses it on the button
		void set_font(char* font, unsigned int font_size = 18);
		//Sets the window to which the button should scale and render
		void set_window(SDL_Window* window);
		//Sets the window the button should be drawn to
		void draw();
		//Updates the button state, based on mouse location and clicks
		void update();
		//Returnes true if the mouse is over the button
		bool is_hovered();
		//Call to set press type (toggle = true, or normal = false)
		void set_toggle(bool ON);
		//Call to get press type (toggle = true, or normal = false)
		bool get_toggle();
	};
}
