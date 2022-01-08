#include<Sprite.h>

ss::Sprite::Sprite(SDL_Window *window, const char* texture) {
	frames = 0;
	frame = 0;
	IMG_Init(IMG_INIT_PNG);
	surface = IMG_Load(texture);
	render = SDL_GetRenderer(window);
	textures = new SDL_Texture * [1];
	Sprite::textures[0] = SDL_CreateTextureFromSurface(render, surface);
	rect = surface->clip_rect;
	rect.x = position.x;
	rect.y = position.y;
	SDL_FreeSurface(surface);
}

ss::Sprite::Sprite(SDL_Window* window, int frames, const char** textures) {
	Sprite::frames = frames;
	frame = 0;
	render = SDL_GetRenderer(window);
	IMG_Init(IMG_INIT_PNG);
	Sprite::textures = new SDL_Texture * [frames];
	for (int i = 0; i < frames; i++) {
		surface = IMG_Load(textures[i]);
		Sprite::textures[i] = SDL_CreateTextureFromSurface(render, surface);
		if (!i) {
			rect = surface->clip_rect;
			rect.x = position.x;
			rect.y = position.y;
		}
		SDL_FreeSurface(surface);
	}
}

void ss::Sprite::load(SDL_Window* window, int frames, const char** textures) {
	for (int i = 0; i < frames; i++) {
		SDL_DestroyTexture(Sprite::textures[i]);
	}
	stop();
	frames = 0;
	IMG_Init(IMG_INIT_PNG);
	Sprite::textures = new SDL_Texture * [frames];
	for (int i = 0; i < frames; i++) {
		surface = IMG_Load(textures[i]);
		Sprite::textures[i] = SDL_CreateTextureFromSurface(render, surface);
		if (!i) {
			rect = surface->clip_rect;
			rect.x = position.x;
			rect.y = position.y;
		}
		SDL_FreeSurface(surface);
	}
}

void ss::Sprite::draw(float delta) {
	if (rect.x != position.x or rect.y != position.y) {
		rect.x = position.x;
		rect.y = position.y;
	}

	if (playing) {
		time += delta / 1000;
		if (reverse) {
			frame = (int)lerp(start, end, 1 - time / anim_time) + 1;
			if (frame < start) {
				if (repeat) {
					frame = end;
					time = 0;
				}
				else {
					playing = false;
					frame = start;
					time = 0;
				}
			}
		}
		else {
			frame = (int)lerp(start, end, time / anim_time);
			if (frame > end) {
				if (repeat) {
					frame = start;
					time = 0;
				}
				else {
					playing = false;
					frame = end;
					time = 0;
				}
			}
		}
	}
	frame = clamp(0, frames, frame);
	SDL_RenderCopyEx(render, textures[frame], NULL, &rect, 0, NULL, flip);
}

void ss::Sprite::play(int start, int end, int fps, bool repeat) {
	if (end < start) {
		reverse = true;
		int aux = start;
		start = end;
		end = aux;
	}
	else {
		reverse = false;
	}
	Sprite::start = start;
	Sprite::end = end;
	Sprite::repeat = repeat;
	anim_time = (double)(end - start) / fps;
	frame = start;
	playing = true;
}

void ss::Sprite::resume() {
	playing = true;
}

void ss::Sprite::stop() {
	frame = 0;
	time = 0;
	playing = false;
}

void ss::Sprite::pause() {
	playing = false;
}

ss::Vector ss::Sprite::get_size() {
	int w, h;
	SDL_QueryTexture(textures[frame], NULL, NULL, &w, &h);
	return Vector(w, h);
}
