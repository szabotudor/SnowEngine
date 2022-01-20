#include<Texture.h>

ss::Texture::Texture(SDL_Window* window, const char* texture, SDL_BlendMode blend_mode) {
	Texture::window = window;
	render = SDL_GetRenderer(window);
	format = SDL_AllocFormat(SDL_GetWindowPixelFormat(window));
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* sfc = IMG_Load(texture);
	Texture::texture = SDL_CreateTextureFromSurface(render, sfc);
	pixels = (Uint32*)sfc->pixels;
	resolution.x = sfc->clip_rect.w;
	resolution.y = sfc->clip_rect.h;
	clip_rect.x = 0;
	clip_rect.y = 0;
	clip_rect.w = 0;
	clip_rect.h = 0;
	SDL_FreeSurface(sfc);
	SDL_SetTextureBlendMode(Texture::texture, blend_mode);
}

ss::Texture::Texture(SDL_Window* window, Vector size, SDL_BlendMode blend_mode) {
	Texture::window = window;
	render = SDL_GetRenderer(window);
	format = SDL_AllocFormat(SDL_GetWindowPixelFormat(window));
	Texture::texture = SDL_CreateTexture(render, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_STATIC, (int)size.x, (int)size.y);
	Texture::resolution = size;
	pixels = new Uint32[(int)size.x * (int)size.y];
	memset(pixels, 0, sizeof(Uint32) * size.x * size.y);
	clip_rect.x = 0;
	clip_rect.y = 0;
	clip_rect.w = 0;
	clip_rect.h = 0;
	SDL_SetTextureBlendMode(Texture::texture, blend_mode);
}

void ss::Texture::draw() {
	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = resolution.x * scale.x;
	rect.h = resolution.y * scale.y;
	if (clip_rect.w or clip_rect.h) {
		SDL_RenderCopy(render, texture, &clip_rect, &rect);
	}
	else {
		SDL_RenderCopy(render, texture, NULL, &rect);
	}
}

void ss::Texture::update() {
	SDL_UpdateTexture(texture, NULL, pixels, sizeof(Uint32) * resolution.x);
}

void ss::Texture::set_pixel(Vector pixel, int r, int g, int b, int a) {
	if (pixel.x >= resolution.x or pixel.y >= resolution.y or pixel.x < 0 or pixel.y < 0) {
		return;
	}
	else {
		pixels[(int)pixel.x + (int)pixel.y * (int)resolution.x] = SDL_MapRGBA(format, r, g, b, a);
	}
}

void ss::Texture::set_pixel(Vector pixel, SDL_Color color) {
	set_pixel(pixel, color.r, color.g, color.b, color.a);
}

SDL_Color ss::Texture::get_pixel(Vector pixel) {
	SDL_Color color{};
	if (pixel.x >= resolution.x or pixel.y >= resolution.y or pixel.x < 0 or pixel.y < 0) {
		color.r = 0;
		color.g = 0;
		color.b = 0;
		color.a = 255;
		return color;
	}
	else {
		SDL_GetRGBA(pixels[(int)pixel.x + (int)pixel.y * (int)resolution.x], format, &color.r, &color.g, &color.b, &color.a);
		return color;
	}
}
