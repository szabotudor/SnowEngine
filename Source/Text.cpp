#include<Text.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
Uint32 rmask = 0xff000000;
Uint32 gmask = 0x00ff0000;
Uint32 bmask = 0x0000ff00;
Uint32 amask = 0x000000ff;
#else
Uint32 rmask = 0x000000ff;
Uint32 gmask = 0x0000ff00;
Uint32 bmask = 0x00ff0000;
Uint32 amask = 0xff000000;
#endif

ss::Text::Text(SDL_Window* window, const char* text, const char* font, Uint8 font_size) {
	if (font_size == 0) {
		throw "Font size must be positive int";
	}
	if (text == "") {
		text = "Text";
	}
	renderer = SDL_GetRenderer(window);
	Text::window = window;
	Text::font = TTF_OpenFont(font, font_size);
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	Text::text = text;
	Text::font_size = font_size;
	set_rich_text(text);
	//Old text init mode
	/*
	surface = TTF_RenderText_Solid(Text::font, text, color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
	*/
}

void ss::Text::set_font(const char* font, Uint8 font_size) {
	Text::font = TTF_OpenFont(font, font_size);
	surface = TTF_RenderText_Solid(Text::font, text.c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	Text::font_size = font_size;
}

void ss::Text::set_text(const char* text) {
	Text::text = text;
	if (text != "\0") {
		surface = TTF_RenderText_Solid(Text::font, text, color);
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		rect.w = surface->w;
		rect.h = surface->h;
		SDL_FreeSurface(surface);
	}
}

void ss::Text::set_text(string text) {
	set_text(text.c_str());
	line_num = 1;
}

void ss::Text::set_rich_text(const char* text) {
	line_num = 0;
	Text::text = text;
	size_t length = strlen(text);
	string t = "";
	int w, h;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	surface = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
	int line = 0;
	int nrt = 0;
	for (int i = 0; i <= length; i++) {
		if (text[i] == '\n' or (i == length and text[i - 1] != '\n')) {
			line_num++;
			if (nrt != 0) {
				nrt = 0;
				SDL_Surface* t_surface = TTF_RenderText_Solid(Text::font, t.c_str(), color);
				SDL_Rect t_rect;
				t_rect.y = (Text::font_size + 2) * line + 1;
				t_rect.x = 1;
				t_rect.w = t_surface->w;
				t_rect.h = t_surface->h;
				SDL_BlitSurface(t_surface, NULL, surface, &t_rect);
				if (surface->w < t_rect.w) {
					surface->w = t_rect.w;
				}
				if (surface->h < t_rect.y + t_rect.h) {
					surface->h = t_rect.h;
				}
				SDL_FreeSurface(t_surface);
				t = "";
			}
			line++;
		}
		if (text[i] != '\n') {
			t += text[i];
			nrt++;
		}
	}
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
}

void ss::Text::set_rich_text(string text) {
	set_rich_text(text.c_str());
}

void ss::Text::draw() {
	if (rect.x != position.x or rect.y != position.y) {
		rect.x = position.x;
		rect.y = position.y;
	}
	if (color.r != prev_color_mod.r or color.g != prev_color_mod.g or color.b != prev_color_mod.b or color.a != prev_color_mod.a) {
		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
		SDL_SetTextureAlphaMod(texture, color.a);
		prev_color_mod = color;
	}
	
	SDL_Rect temp_rect{};
	temp_rect.w = rect.w * scale;
	temp_rect.h = rect.h * scale;
	temp_rect.x = rect.x - temp_rect.w / 2;
	temp_rect.y = rect.y - temp_rect.h / 2;
	SDL_RenderCopyEx(renderer, texture, NULL, &temp_rect, angle, NULL, SDL_FLIP_NONE);
	//SDL_RenderCopy(renderer, texture, NULL, &rect);
}

string ss::Text::get_text() {
	return Text::text;
}

int ss::Text::get_num_of_lines() {
	return line_num;
}
