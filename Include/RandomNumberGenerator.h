#pragma once
#include<chrono>
#include<iostream>
#include<Vector.h>
using namespace std;


namespace ss {
	class RandomNumberGenerator {
		long long k1 = 159979, k2 = 153611, k3 = 148021;
		int init = -1;
	public:
		long long seed = 0;
		RandomNumberGenerator(long long seed = 0);
		//Sets the seed to the system clock to randomize the generator
		void randomize();
		//Returns the first itteration of the rng generator (can be used to generate other types of random numbers)
		long long rand();
		//Returns a random float between 0 and 1 (or a between 0 and another number, if given)
		float randf(float k = 1);
		//Returns a random float between a given range
		float randf_range(float min, float max);
		//Returns a random double between 0 and 1 (or a between 0 and another number, if given)
		double randd(double k = 1);
		//Returns a random double between a given range
		double randd_range(double min, double max);
		//Returns a random int between 0 and 100 (or between 0 and another number, if given)
		int randi(int k = 100);
		//Returns a random int between a given range
		int randi_range(int min, int max);
		//Returns a random Vector between (0, 0) and (1, 1) (or a between (0, 0) and another Vector, if given)
		Vector randv(Vector k = 1);
		//Returns a random Vector between a given range
		Vector randv_range(Vector min, Vector max);
		//Returns a random direction vector that has been normalized
		Vector randdir();
	};
}
