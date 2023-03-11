#pragma once
#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"
#include "vec3.h"

class sphere :public hittable {
public:
	sphere();
	sphere(point3 cen, double r) :center(cen), radius(r) {};
	virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& rec) const override;


private:
	point3 center;
	double radius;
};


bool sphere::hit(const ray& ray, double t_min, double t_max, hit_record& rec) const
{
	auto oc = ray.orign() - center;
	auto a = ray.direction().length_squared();
	auto half_b = dot(oc, ray.direction());
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
	{
		return false;
	}
	auto sqrtd = sqrt(discriminant);
	auto t = (-half_b -sqrtd) / a;
	if (t<t_min || t> t_max)
	{
		t = (-half_b + sqrtd) / a;
		if (t<t_min || t> t_max)
		{
			return false;
		}
	}
	rec.t = t;
	rec.pos = ray.at(t);
	rec.normal = (rec.pos - center)/radius;		//P-Cµƒæ‡¿Î“ª∂® = radius

	return true;
}



#endif // !SPHERE_H
