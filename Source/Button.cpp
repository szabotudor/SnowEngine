#include<Snow.h>

ss::Button::Button(SDL_Window* window, const char* text, const char* font, unsigned int font_size) {
	Button::font = TTF_OpenFont(font, font_size);
	Button::window = window;
	if (text == "") {
		text = "BUTTON";
	}
	render = SDL_GetRenderer(window);
	SDL_RenderGetViewport(render, &viewport);
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	text_color.a = 255;
	surface = TTF_RenderText_Solid(Button::font, text, text_color);
	texture = SDL_CreateTextureFromSurface(render, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
	Button::text = text;
	Button::font_size = font_size;

	background_type = BackgroundType::Empty;
	type = Type::Press;
}

ss::Button::Button(SDL_Window* window, SDL_Color bgd_color, SDL_Color border_color, SDL_Color text_color, unsigned int border_thickness, const char* text, const char* font, unsigned int font_size) {
	Button::font = TTF_OpenFont(font, font_size);
	Button::window = window;
	if (text == "") {
		text = "BUTTON";
	}
	render = SDL_GetRenderer(window);
	SDL_RenderGetViewport(render, &viewport);
	Button::text_color = text_color;
	Button::fill_color = bgd_color;
	Button::border_color = border_color;
	border = border_thickness;
	surface = TTF_RenderText_Solid(Button::font, text, text_color);
	texture = SDL_CreateTextureFromSurface(render, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	border_rect.x = -border;
	border_rect.y = -border;
	border_rect.w = surface->w + border * 2;
	border_rect.h = surface->h + border * 2;
	SDL_FreeSurface(surface);
	Button::text = text;
	Button::font_size = font_size;

	background_type = BackgroundType::Rect;
	type = Type::Press;
}

ss::Button::Button(SDL_Window* window, SDL_Color text_color, const char* text, const char* font, unsigned int font_size) {
	Button::font = TTF_OpenFont(font, font_size);
	Button::window = window;
	if (text == "") {
		text = "BUTTON";
	}
	render = SDL_GetRenderer(window);
	SDL_RenderGetViewport(render, &viewport);
	Button::text_color = text_color;
	surface = TTF_RenderText_Solid(Button::font, text, text_color);
	texture = SDL_CreateTextureFromSurface(render, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
	Button::text = text;
	Button::font_size = font_size;

	background_type = BackgroundType::Empty;
	type = Type::Press;
}

void ss::Button::set_text(char* text) {
	surface = TTF_RenderText_Solid(Button::font, text, text_color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(render, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
	Button::text = text;
}

string ss::Button::get_text() {
	return text;
}

void ss::Button::set_font(char* font, unsigned int font_size) {
	Button::font = TTF_OpenFont(font, font_size);
}

void ss::Button::set_window(SDL_Window* window) {
	Button::window = window;
	render = SDL_GetRenderer(window);
}

void ss::Button::draw() {
	position += draw_offset;
	if (rect.x != position.x or rect.y != position.y) {
		rect.x = position.x;
		rect.y = position.y;
		border_rect.x = position.x - border;
		border_rect.y = position.y - border;
	}
	position -= draw_offset;
	switch (background_type) {
	case ss::Button::BackgroundType::Rect:
		SDL_SetRenderDrawColor(render, border_color.r, border_color.g, border_color.b, border_color.a);
		SDL_RenderFillRect(render, &border_rect);
		SDL_SetRenderDrawColor(render, fill_color.r, fill_color.g, fill_color.b, fill_color.a);
		SDL_RenderFillRect(render, &rect);
		SDL_SetRenderDrawColor(render, text_color.r, text_color.g, text_color.b, text_color.a);
		SDL_RenderCopy(render, texture, NULL, &rect);
	case ss::Button::BackgroundType::Empty:
		SDL_RenderCopy(render, texture, NULL, &rect);
	case ss::Button::BackgroundType::Texture:
		break;
	}
}

void ss::Button::update() {
	bounding_box.position = position;
	SDL_RenderGetViewport(render, &viewport);
	bounding_box.size = Vector(rect.w, rect.h);
	hovered = is_hovered();
	int x, y;
	Uint32 mouse_state = SDL_GetMouseState(&x, &y);

	bool last_press = pressed;
	switch (type) {
	case ss::Button::Type::Press:
		pressed = mouse_state & SDL_BUTTON_LMASK and hovered;
		break;
	case ss::Button::Type::Toggle:
		if (mouse_state & SDL_BUTTON_LMASK and hovered) {
			if (!held) {
				pressed = !pressed;
				held = true;
			}
		}
		else {
			held = false;
		}
		break;
	}

	just_pressed = !last_press and pressed;
	just_released = last_press and !pressed;
}

bool ss::Button::is_hovered() {
	rect.x = position.x;
	rect.y = position.y;
	int x, y;
	float rx, ry;
	SDL_GetMouseState(&x, &y);
	SDL_RenderGetScale(render, &rx, &ry);
	x -= viewport.x * rx;
	y -= viewport.y * ry;
	//bounding_box.size = Vector(rect.w * rx, rect.h * ry);
	return x > rect.x * rx and x < rect.x * rx + rect.w * rx and y > rect.y * ry and y < rect.y*ry + rect.h * ry;
}

void ss::Button::set_toggle(bool ON) {
	if (ON) {
		type = Type::Toggle;
	}
	else {
		type = Type::Press;
	}
}

bool ss::Button::get_toggle() {
	return type == Type::Toggle;
}
