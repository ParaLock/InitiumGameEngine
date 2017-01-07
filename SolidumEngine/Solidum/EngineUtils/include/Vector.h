#pragma once

template<unsigned dim>
struct Vector
{
	float d[dim];

	template<typename ...T>
	Vector(T&&... args) : d{ args... } {}

	float operator[] (unsigned n) const { return d[n]; }
};
