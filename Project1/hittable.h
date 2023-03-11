#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
	point3 pos;
	double t;
	vec3 normal;
	bool front_face;	//是否为正面
	//让normal始终与射线相反，并标记是正面还是内部
	inline void set_face_normal(const ray& r, const vec3& out_normal) {
		front_face = dot(r.direction(), normal) < 0;
		normal = front_face ? out_normal : -out_normal;
	}
};

class hittable {
public:
	virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif // !HITTABLE_H
