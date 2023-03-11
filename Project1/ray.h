#pragma once
#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
private:
	point3 orig;
	vec3 dir;
public:
	ray(){}
	ray(const point3& orign, const vec3& dir) :orig(orign), dir(dir) {};
	point3 orign() const { return orig; }
	vec3 direction() const { return dir; }
	point3 at(double t) {
		return point3(orig + dir * t);
	}
};

#endif // !RAY_H
