#include<RandomNumberGenerator.h>

ss::RandomNumberGenerator::RandomNumberGenerator(long long seed) {
	RandomNumberGenerator::seed = seed;
	init = rand();
}

void ss::RandomNumberGenerator::randomize() {
	const auto p1 = chrono::system_clock::now();
	seed = p1.time_since_epoch().count();
}

long long ss::RandomNumberGenerator::rand() {
	seed = (seed * k1 + k2) % k3;
	if (seed == init) {
		k2++;
		init = rand();
	}
	return seed;
}

float ss::RandomNumberGenerator::randf(float k) {
	return (float)rand() / k3 * k;
}

float ss::RandomNumberGenerator::randf_range(float min, float max) {
	return (float)rand() / k3 * (max - min) + min;
}

double ss::RandomNumberGenerator::randd(double k) {
	return (double)rand() / k3 * k;
}

double ss::RandomNumberGenerator::randd_range(double min, double max) {
	return (double)rand() / k3 * (max - min) + min;
}

int ss::RandomNumberGenerator::randi(int k) {
	return (int)((float)rand() / k3 * (k + 1));
}

int ss::RandomNumberGenerator::randi_range(int min, int max) {
	return (int)((float)rand() / k3 * (max - min + 1) + min);
}

ss::Vector ss::RandomNumberGenerator::randv(Vector k) {
	return Vector((float)rand() / k3 * k.x, (float)rand() / k3 * k.y);
}

ss::Vector ss::RandomNumberGenerator::randv_range(Vector min, Vector max) {
	return Vector((float)rand() / k3 * (max - min).x + min.x, (float)rand() / k3 * (max - min).y + min.y);
}

ss::Vector ss::RandomNumberGenerator::randdir() {
	return randv_range(-1, 1).normalized();
}
