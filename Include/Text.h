#pragma once
#include<Snow.h>


namespace ss {
	class Text {
		Uint8 font_size = 0;
		string text = "";
		SDL_Color prev_color_mod;
		TTF_Font* font;
		SDL_Texture* texture;
		SDL_Surface* surface;
		SDL_Renderer* renderer;
		SDL_Window* window;
		SDL_Rect rect;
		int line_num = 0;
	public:
		SDL_Color color;
		Vector position;
		Text(SDL_Window* window, const char* text, const char* font, Uint8 font_size = 18);
		//Sets the font file given as the Text object's font
		void set_font(const char* font, Uint8 font_size);
		//Sets the text to the given string
		void set_text(const char* text);
		//Sets the text to the given string
		void set_text(string text);
		//Sets the text to the given string, taking into consideration command characters
		void set_rich_text(const char* text);
		//Sets the text to the given string, taking into consideration command characters
		void set_rich_text(string text);
		//Draws the text on screen
		void draw();
		//Returns the text set on the Text object
		string get_text();
		//Returns the number of lines
		int get_num_of_lines();
	};
}
