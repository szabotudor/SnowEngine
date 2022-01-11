#include<Texture.h>

ss::Texture::Texture(SDL_Window* window, const char* texture) {
	Texture::window = window;
	render = SDL_GetRenderer(window);
	format = SDL_AllocFormat(SDL_GetWindowPixelFormat(window));
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* sfc = IMG_Load(texture);
	Texture::texture = SDL_CreateTextureFromSurface(render, sfc);
	pixels = (Uint32*)sfc->pixels;
	size.x = sfc->clip_rect.w;
	size.y = sfc->clip_rect.h;
	SDL_FreeSurface(sfc);
}

ss::Texture::Texture(SDL_Window* window, Vector size) {
	Texture::window = window;
	render = SDL_GetRenderer(window);
	format = SDL_AllocFormat(SDL_GetWindowPixelFormat(window));
	Texture::texture = SDL_CreateTexture(render, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_STATIC, (int)size.x, (int)size.y);
	Texture::size = size;
	pixels = new Uint32[(int)size.x * (int)size.y];
	memset(pixels, 0, sizeof(Uint32) * size.x * size.y);
}

void ss::Texture::draw() {
	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = size.x;
	rect.h = size.y;
	SDL_RenderCopy(render, texture, NULL, &rect);
}

void ss::Texture::update() {
	SDL_UpdateTexture(texture, NULL, pixels, sizeof(Uint32) * size.x);
}

void ss::Texture::set_pixel(Vector pixel, int r, int g, int b, int a) {
	if (pixel.x >= size.x or pixel.y >= size.y) {
		return;
	}
	pixels[(int)pixel.x + (int)pixel.y * (int)size.x] = SDL_MapRGB(format, r, g, b);
}

void ss::Texture::set_pixel(Vector pixel, SDL_Color color) {
	set_pixel(pixel, color.r, color.g, color.b, color.a);
}

SDL_Color ss::Texture::get_pixel(Vector pixel) {
	SDL_Color color;
	color.r = pixels[(int)pixel.x + (int)pixel.y * (int)size.x] >> 16;
	color.g = pixels[(int)pixel.x + (int)pixel.y * (int)size.x] >> 8;
	color.b = pixels[(int)pixel.x + (int)pixel.y * (int)size.x];
	return color;
}
