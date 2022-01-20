#pragma once
#include<SDL.h>
#include<RandomNumberGenerator.h>
#include<Vector.h>
#include<iostream>
using namespace std;

namespace ss {
	class ParticleEmitter {
	public:
		enum class EmissionShape {
			POINT,
			CIRCLE,
			RECT,
			LINE
		};
		enum class GravityType {
			DIRECTION,
			POINT
		};
		class ParticleType {
			SDL_Color* gradient = nullptr;
			double* gradient_times = nullptr;
			int colors = 0;

			double* scale_curve = nullptr;
			double* scale_times = nullptr;
			int scales = 0;
			double max_scale;
		public:
			SDL_Texture* texture;
			double lifelimit = 1.0;
			double lifetime_random = 0;
			double velocity_damping = 0.0125;
			double angular_velocity_damping = 0.0125;

			GravityType g_type = GravityType::DIRECTION;
			double g_force = 1;
			Vector g_direction = Vector(0, 1);
			Vector g_position = Vector();
			bool use_gravity = false;

			double initial_velocity_min = 0;
			double initial_velocity_max = 0;
			double initial_direction_randomness = 0.0;
			Vector initial_direction = Vector(0, 0);
			Vector initial_velocity = 0;

			double initial_angular_velocity_min = 0.0;
			double initial_angular_velocity_max = 0.0;

			//Adds a new color to the color gradient list
			void add_color_to_gradient(SDL_Color color, double timestamp);
			//Adds a new color to the color gradient list
			void add_color_to_gradient(int r, int g, int b, double timestamp);
			//Returns the color with which the particle will be drawn at a certain timestamp
			SDL_Color get_color_at_timestamp(double time);
			//Returns the ammount of colors added to the gradient
			int get_colors_in_gradient();

			//Adds a new scale to the scale curve list
			void add_scale_to_scale_curve(double scale, double timestamp);
			//Returns the scale at a certain timestamp
			double get_scale_at_timestamp(double time);
			//Returns the number of scales in the scale curve
			int get_scales_in_scale_curve();
			//(do not use this, it is inteded for internal use of the particle emitter only) Frees all memory used by particle layer
			void free();
		};
	private:
		RandomNumberGenerator rng = RandomNumberGenerator(98132479);
		ParticleEmitter* sec_emitter;
		bool use_sec_emitter = false;
		SDL_Window* window;
		SDL_Renderer* render;
		int max_ammount = 0;
		int ammount = 0;
		int layer = 0;

		double* p_lifetime;
		Vector* p_position;
		Vector* p_velocity;
		double* p_angle;
		double* p_angular_velocity;
		int* p_layer;
		int* p_order;
		bool* p_drawn;
		bool* p_first_reset;

		bool init = false;
	public:
		bool sort_by_lifetime = false;
		bool reverse_draw_order = false;
		bool one_time = false;
		ParticleType* particle_layer;
		EmissionShape emission_shape = EmissionShape::POINT;
		double emission_radius = 1;
		Vector position;
		Vector draw_offset;

		ParticleEmitter(SDL_Window* window, Vector position, bool sort_by_lifetie = false);
		//Adds a specified ammount of the given particle into the next free layer
		void add_particle_layer(int ammount, SDL_Texture* texture, double lifelimit, double explosiveness);
		//Adds a seccondary emitter (actiong as a seccond layer of particles)
		void add_seccondary_emitter(ParticleEmitter* emitter);
		//Turns off and removes the seccondary emitter (if it exists)
		void remove_seccondary_emitter();
		//Updates position of al particles
		void update(double delta);
		//Draws all particles in the emitter on the screen
		void draw();
		//Returns the number of particle layers in the emitter
		int get_num_of_layers();
		//Returns the total number of particles
		int get_num_of_particles();
		//Returns the global position of a particle
		Vector get_particle_position(int i);
		//Returns the lifetime of a particle
		double get_particle_lifetime(int i);
		//Sets the position of the given particle
		void set_particle_position(int i, Vector pos);
		//Set the ammount of particles to be drawn
		void set_draw_ammount(int ammount);
		//Frees all memory used by the particle emitter
		void free();
	};
}
