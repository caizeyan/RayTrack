#pragma once
#ifndef RTWEEKEND_H
#define RTWEEKEN_H

//常量和工具方法
#include <cmath>
#include <limits>
#include <memory>

//Headers
#include "ray.h"
#include "vec3.h"

//Using
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility Func
inline double degrees_to_radians(double degree) {
	return degree * pi / 180;
}


#endif // !RTWEEKEND_H

