#pragma once
#include<SDL.h>
#include<Particles.h>
#include<Vector.h>


namespace ss {
	void resize(int start_size, int end_size, ss::Vector*& arr);
	void resize(int start_size, int end_size, double*& arr);
	void resize(int start_size, int end_size, SDL_Texture**& arr);
	void resize(int start_size, int end_size, int*& arr);
	void resize(int start_size, int end_size, int**& arr);
	void resize(int start_size, int end_size, ParticleEmitter::ParticleType*& arr);
	void resize(int start_size, int end_size, bool*& arr);
	void resize(int start_size, int end_size, SDL_Event*& arr);
	void resize(int start_size, int end_size, SDL_Color*& arr);

	Vector lerp(Vector start, Vector end, double weight);
	double lerp(double start, double end, double weight);

	double clamp(double min, double max, double val);

	double natural(double val);
	int natural(int val);
	long long natural(long long val);
}
