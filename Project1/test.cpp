#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

color ray_color(const ray& r,const hittable& world) {
    hit_record record;
    if (world.hit(r,0,infinity,record) )
    {
        return 0.5 * color(record.normal + vec3(1, 1, 1));
    }
    //��Ϊ�и� unit ˮƽ������t�������ټ�С����ֱ�����ϻ�����
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

    //World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));


    //Camera
    auto  viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;   //����Ƭ�����һ�£�ȷ�����ش���ƽ̨�ϲ�������
    auto focal_length = 1.0;                        //�����ƽ̨����

    point3 origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rline:"<<  j << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            color pixel_color = ray_color(r,world);
            
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone\n";
}