#include<Utility.h>

//================
//	Resize code
//================

void ss::resize(int start_size, int end_size, ss::Vector*& arr) {
	if (start_size == 0) {
		delete[] arr;
		arr = new ss::Vector[end_size];
	}
	else {
		ss::Vector* n_arr = new ss::Vector[end_size];
		for (int i = 0; i < start_size; i++) {
			n_arr[i] = arr[i];
		}
		ss::Vector* temp = arr;
		arr = n_arr;
		delete[] temp;
	}
}

void ss::resize(int start_size, int end_size, double*& arr) {
	if (start_size == 0) {
		arr = new double[end_size];
	}
	else {
		double* n_arr = new double[end_size];
		for (int i = 0; i < start_size; i++) {
			n_arr[i] = arr[i];
		}
		double* temp = arr;
		arr = n_arr;
		delete[] temp;
	}
}

void ss::resize(int start_size, int end_size, SDL_Texture**& arr) {
	if (start_size == 0) {
		delete[] arr;
		arr = new SDL_Texture * [end_size];
	}
	else {
		SDL_Texture** n_arr = new SDL_Texture * [end_size];
		for (int i = 0; i < start_size; i++) {
			n_arr[i] = arr[i];
		}
		SDL_Texture** temp = arr;
		arr = n_arr;
		delete[] temp;
	}
}

void ss::resize(int start_size, int end_size, int*& arr) {
	if (start_size == 0) {
		delete[] arr;
		arr = new int[end_size];
	}
	else {
		int* n_arr = new int[end_size];
		for (int i = 0; i < start_size; i++) {
			n_arr[i] = arr[i];
		}
		int* temp = arr;
		arr = n_arr;
		delete[] temp;
	}
}

void ss::resize(int start_size, int end_size, int**& arr) {
	if (start_size == 0) {
		delete[] arr;
		arr = new int* [end_size];
	}
	else {
		int** n_arr = new int* [end_size];
		for (int i = 0; i < start_size; i++) {
			n_arr[i] = arr[i];
		}
		int** temp = arr;
		arr = n_arr;
		delete[] temp;
	}
}

void ss::resize(int start_size, int end_size, ParticleEmitter::ParticleType*& arr) {
	if (start_size == 0) {
		delete[] arr;
		arr = new ParticleEmitter::ParticleType[end_size];
	}
	else {
		ParticleEmitter::ParticleType* n_arr = new ParticleEmitter::ParticleType[end_size];
		for (int i = 0; i < start_size; i++) {
			n_arr[i] = arr[i];
		}
		ParticleEmitter::ParticleType* temp = arr;
		arr = n_arr;
		delete[] temp;
	}
}

void ss::resize(int start_size, int end_size, bool*& arr) {
	if (start_size == 0) {
		delete[] arr;
		arr = new bool[end_size];
	}
	else {
		bool* n_arr = new bool[end_size];
		for (int i = 0; i < start_size; i++) {
			n_arr[i] = arr[i];
		}
		bool* temp = arr;
		arr = n_arr;
		delete[] temp;
	}
}

void ss::resize(int start_size, int end_size, SDL_Event*& arr) {
	if (start_size == 0) {
		delete[] arr;
		arr = new SDL_Event[end_size];
	}
	else {
		SDL_Event* n_arr = new SDL_Event[end_size];
		for (int i = 0; i < start_size; i++) {
			n_arr[i] = arr[i];
		}
		SDL_Event* temp = arr;
		arr = n_arr;
		delete[] temp;
	}
}

void ss::resize(int start_size, int end_size, SDL_Color*& arr) {
	if (start_size == 0) {
		arr = new SDL_Color[end_size];
	}
	else {
		SDL_Color* n_arr = new SDL_Color[end_size];
		for (int i = 0; i < start_size; i++) {
			n_arr[i] = arr[i];
		}
		SDL_Color* temp = arr;
		arr = n_arr;
		delete[] temp;
	}
}

//===============
//	Lerp code
//===============

ss::Vector ss::lerp(Vector start, Vector end, double weight) {
	start.x += (end.x - start.x) * weight;
	start.y += (end.y - start.y) * weight;
	return start;
}

double ss::lerp(double start, double end, double weight) {
	start += (end - start) * weight;
	return start;
}

double ss::clamp(double min, double max, double val) {
	if (val > max) {
		val = max;
	}
	else if (val < min) {
		val = min;
	}
	return val;
}

double ss::natural(double val) {
	if (val >= 0) {
		return val;
	}
	else {
		return -val;
	}
}

int ss::natural(int val) {
	if (val >= 0) {
		return val;
	}
	else {
		return -val;
	}
}

long long ss::natural(long long val) {
	if (val >= 0) {
		return val;
	}
	else {
		return -val;
	}
}
