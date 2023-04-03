#include "rtweekend.h"
//Headers
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

color ray_color(const ray& r,const hittable& world,int depth) {
    if (depth <= 0)
    {
        return color(0, 0, 0);
    }
    hit_record record;
 
    //两个相同的数相减不一定完全=0  有可能为0.0000001 
    if (world.hit(r,0.0001,infinity,record) )
    {
        point3 target = record.pos + record.normal + random_unit_vector();
        return 0.5 * ray_color(ray(record.pos, target - record.pos), world,depth-1);
   
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
    const int samples_per_pixel = 100;
    const int max_depth = 10;
    //World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));


    //Camera
    camera cam;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rline:"<<  j << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                //-1的含义，左下角值开始(0,0) 坐标最大值为(image_width-1,image_height-1)
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray ray= cam.get_ray(u, v);
                pixel_color += ray_color(ray,world,max_depth);
            }
            write_color(std::cout, pixel_color,samples_per_pixel);
        }
    }
    std::cerr << "\nDone\n";
}