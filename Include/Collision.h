#pragma once
#include<Utility.h>
#include<iostream>
#include<Vector.h>
#include<SDL.h>

using namespace std;

namespace ss {
	class CollisionShape {
		SDL_Window* window;
		SDL_Renderer* render;
		bool draw_enabled = false;
		SDL_Rect rect;
	public:
		Vector position;
		Vector size;
		SDL_Color draw_color;
		CollisionShape(Vector size = Vector(1), Vector position = Vector(0), SDL_Window* window = nullptr);
		//Returns true if this is overlapping with the given CollisionShape
		bool is_colliding_with(CollisionShape cs, bool inverse_collision = false);
		//Returns true if the vector is inside the CollisionShape
		bool is_colliding_with(Vector v);
		//Pushes the given CollisionShape out of this one
		void push_out(CollisionShape& cs);
		//Pushes the given Vector out of the CollisionShape
		void push_out(Vector& v);
		//Pushes the given CollisionShape into this one
		void push_in(CollisionShape& cs);
		//Pushes the given Vector into the CollisionShape
		void push_in(Vector& v);
		//Enables drawing of the CollisionShape to the window (usually only used in debug)
		void enable_draw(SDL_Window* window);
		//Draws the CollisionShape to the window (usually only used in debug)
		void draw();
		//Returns the area of the CollisionShape
		double get_area();
		//Returns the coordinates of the center of the CollisionShape
		Vector get_center();
	};
}
