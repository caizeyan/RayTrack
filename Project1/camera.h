#pragma once

#include "rtweekend.h"

class camera {
private:
	//摄像机原点 世界坐标
	point3 origin;
	//屏幕左下脚 世界坐标
	point3 lower_left_corner;
	//水平向量和垂直向量 用来做归一化 以及将uv坐标转换为世界坐标
	vec3 horizontal;
	vec3 vertical;

public:
	camera() {
		auto aspect_ratio = 16.0 / 9.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * aspect_ratio;
		auto focal_length = 1.0;

		origin = point3(0, 0, 0);
		horizontal = vec3(viewport_width, 0, 0);
		vertical = vec3(0, viewport_height, 0);
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length);
	}

	ray get_ray(double u, double v) {
		return ray(origin, lower_left_corner + u * horizontal + v * vertical-origin);
	}
};
