#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>

bool hit_sphere(const point3& center, const double radiu, const ray& ray)
{
    auto ac = ray.orign() - center;
    auto a = dot(ray.direction(), ray.direction());
    auto b = 2 * dot(ray.direction(), ac);
    auto c = dot(ac, ac)-radiu*radiu; 
    return (b * b - 4 * a * c) >= 0;
}

color ray_color(const ray& r) {
    if (hit_sphere(point3(0,0,-1),0.5,r))
    {
        return color(1, 0, 0);
    }
    //因为有个 unit 水平方向上t先增大再减小，竖直方向上会增大
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1);
    //a stand lerp (white to blue)
    return (1 - t) * color(1, 1, 1) + t * color(0.5, 0.7, 1);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //Camera
    auto  viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;   //与照片长宽比一致，确保像素打在平台上不会缩放
    auto focal_length = 1.0;                        //相机与平台距离

    point3 origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining:" << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            color pixel_color = ray_color(r);
            
            // color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone\n";
}