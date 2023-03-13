#pragma once
#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

void write_color(std::ostream &out, color pixel_color) {
	out << static_cast<int>(255.999 * pixel_color[0]) << ' '
		<< static_cast<int>(255.999 * pixel_color[1]) << ' '
		<< static_cast<int>(255.999 * pixel_color[2]) << std::endl;
}

void write_color(std::ostream& out, color pixel_color,int samples_per_pixel) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	auto scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	//clamp 防止取值不正确
	out << static_cast<int>(255.999 * clamp( r,0,0.999)) << ' '
		<< static_cast<int>(255.999 * clamp(g, 0, 0.999)) << ' '
		<< static_cast<int>(255.999 * clamp(b, 0, 0.999)) << std::endl;
}

#endif // !COLOR_H
