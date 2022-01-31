#include<Vector.h>
#include<math.h>

/*
=======================
Vector Code
=======================
*/

ss::Vector::Vector(float x, float y) {
	Vector::x = x;
	Vector::y = y;
}

ss::Vector::Vector(float w) {
	Vector::x = w;
	Vector::y = w;
}

//Classic number operators
ss::Vector ss::Vector::operator+(float x) {
	return Vector(this->x + x, this->y + x);
}

ss::Vector ss::Vector::operator-(float x) {
	return Vector(this->x - x, this->y - x);
}

ss::Vector ss::Vector::operator*(float x) {
	return Vector(this->x * x, this->y * x);
}

ss::Vector ss::Vector::operator/(float x) {
	return Vector(this->x / x, this->y / x);
}

//Auto operators
void ss::Vector::operator+=(float x) {
	this->x += x;
	this->y += x;
}

void ss::Vector::operator-=(float x) {
	this->x -= x;
	this->y -= x;
}

void ss::Vector::operator*=(float x) {
	this->x *= x;
	this->y *= x;
}

void ss::Vector::operator/=(float x) {
	this->x /= x;
	this->y /= x;
}

void ss::Vector::operator+=(Vector v) {
	this->x += v.x;
	this->y += v.y;
}

void ss::Vector::operator-=(Vector v) {
	this->x -= v.x;
	this->y -= v.y;
}

void ss::Vector::operator*=(Vector v) {
	this->x *= v.x;
	this->y *= v.y;
}

void ss::Vector::operator/=(Vector v) {
	this->x /= v.x;
	this->y /= v.y;
}

bool ss::Vector::operator==(Vector v) {
	return x == v.x and y == v.y;
}

bool ss::Vector::operator!=(Vector v) {
	return x != v.x or y != v.y;
}

//Full vector operators
ss::Vector ss::Vector::operator+(Vector v) {
	return Vector(this->x + v.x, this->y + v.y);
}

ss::Vector ss::Vector::operator-(Vector v) {
	return Vector(this->x - v.x, this->y - v.y);
}

ss::Vector ss::Vector::operator*(Vector v) {
	return Vector(this->x * v.x, this->y * v.y);
}

ss::Vector ss::Vector::operator/(Vector v) {
	return Vector(this->x / v.x, this->y / v.y);
}

//Set operator
ss::Vector ss::Vector::operator=(float x) {
	return Vector(x, x);
}

ss::Vector ss::Vector::normalized() {
	float n = this->lenght();
	if (x or y) {
		return Vector(this->x / n, this->y / n);
	}
	else {
		return Vector(0, 0);
	}
}

void ss::Vector::normalize() {
	if (x or y) {
		float n = this->lenght();
		x = this->x / n;
		y = this->y / n;
	}
	else {
		x = 0;
		y = 0;
	}
}

float ss::Vector::lenght() {
	return (float)sqrt(this->x * this->x + this->y * this->y);
}

ss::Vector ss::Vector::direction_to(Vector v) {
	return Vector(v.x - Vector::x, v.y - Vector::y).normalized();
}

double ss::Vector::distance_to(Vector v) {
	return sqrt((v.x - Vector::x) * (v.x - Vector::x) + (v.y - Vector::y) * (v.y - Vector::y));
}
