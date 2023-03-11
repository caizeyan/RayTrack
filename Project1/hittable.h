#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
	point3 pos;
	double t;
	vec3 normal;
};

class hittable {
public:
	virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif // !HITTABLE_H
