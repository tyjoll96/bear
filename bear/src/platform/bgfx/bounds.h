#pragma once

#ifndef BOUNDS_H_HEADER_GUARD
#define BOUNDS_H_HEADER_GUARD

#include <bx/math.h>

///
struct Aabb
{
	bx::Vec3 min;
	bx::Vec3 max;
};

///
struct Obb
{
	float mtx[16];
};

///
struct Sphere
{
	bx::Vec3 center;
	float    radius;
};

#endif // BOUNDS_H_HEADER_GUARD