#include<Collision.h>

ss::CollisionShape::CollisionShape(Vector size, Vector position, SDL_Window* window) {
	CollisionShape::position = position;
	CollisionShape::size = size;
	if (window != nullptr) {
		CollisionShape::window = window;
		render = SDL_GetRenderer(window);
		draw_enabled = true;
	}
	draw_color.r = 120;
	draw_color.g = 120;
	draw_color.b = 255;
}

bool ss::CollisionShape::is_colliding_with(CollisionShape cs, bool inverse_collision) {
	if (!inverse_collision) {
		return (position.x + size.x > cs.position.x and position.y + size.y > cs.position.y) and
			(position.x < cs.position.x + cs.size.x and position.y < cs.position.y + cs.size.y);
	}
	else {
		return (position.x < cs.position.x or position.y < cs.position.y) or
			(position.x + size.x > cs.position.x + cs.size.x or position.y + size.y > cs.position.y + cs.size.y);
	}
}

bool ss::CollisionShape::is_colliding_with(Vector v) {
	return v.x > position.x and v.x < position.x + size.x and v.y > position.y and v.y < position.y + size.y;
}

void ss::CollisionShape::push_out(CollisionShape& cs) {
	if (is_colliding_with(cs)) {
		Vector cs_center = cs.get_center();
		Vector center = get_center();
		Vector depth;
		if (cs_center.x <= center.x) {
			depth.x = cs.position.x + cs.size.x - position.x;
		}
		else {
			depth.x = -(position.x + size.x - cs.position.x);
		}

		if (cs_center.y <= center.y) {
			depth.y = cs.position.y + cs.size.y - position.y;
		}
		else {
			depth.y = -(position.y + size.y - cs.position.y);
		}

		if (natural(depth.x) > natural(depth.y)) {
			cs.position.y -= depth.y;
		}
		else {
			cs.position.x -= depth.x;
		}
	}
}

void ss::CollisionShape::push_out(Vector& v) {
	if (is_colliding_with(v)) {
		Vector center = get_center();
		if (v.x < center.x) {
			v.x = position.x;
		}
		else {
			v.x = position.x + size.x;
		}
		if (v.y < center.y) {
			v.y = position.y;
		}
		else {
			v.y = position.y + size.y;
		}
	}
}

void ss::CollisionShape::push_in(CollisionShape& cs) {
	if (is_colliding_with(cs, true)) {
		if (cs.position.x < position.x) {
			cs.position.x = position.x;
		}
		else if (cs.position.x + cs.size.x > position.x + size.x) {
			cs.position.x = position.x + size.x - cs.size.x;
		}

		if (cs.position.y < position.y) {
			cs.position.y = position.y;
		}
		else if (cs.position.y + cs.size.y > position.y + size.y) {
			cs.position.y = position.y + size.y - cs.size.y;
		}
	}
}

void ss::CollisionShape::push_in(Vector& v) {
	if (!is_colliding_with(v)) {
		if (v.x < position.x) {
			v.x = position.x;
		}
		else if (v.x > position.x + size.x) {
			v.x = position.x + size.x;
		}
		if (v.y < position.y) {
			v.y = position.y;
		}
		else if (v.y > position.y + size.y) {
			v.y = position.y + size.y;
		}
	}
}

void ss::CollisionShape::enable_draw(SDL_Window* window) {
	CollisionShape::window = window;
	render = SDL_GetRenderer(window);
	draw_enabled = true;
}

void ss::CollisionShape::draw() {
	rect.x = position.x;
	rect.y = position.y;
	rect.w = size.x;
	rect.h = size.y;
	SDL_SetRenderDrawColor(render, draw_color.r, draw_color.g, draw_color.b, draw_color.a);
	SDL_RenderDrawRect(render, &rect);
	Vector center = get_center();
	SDL_RenderDrawPoint(render, center.x, center.y);
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
}

double ss::CollisionShape::get_area() {
	return size.x * size.y;
}

ss::Vector ss::CollisionShape::get_center() {
	return position + (size / 2);
}
