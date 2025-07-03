#include "ABConst.h"
#include "Vec3.h"
#include "color.h"
#include "hittable.h"
#include "material.h"
#include <cmath>

class camera {
public:
  double aspect_ratio = 16.0f / 9.0f;
  int image_width = 800;
  int maxDepth = 10;
  int sample_per_pixel = 10;
  double vfov = 45.0;
  vec3 lookfrom = vec3(0, 0, 0);
  vec3 lookat = vec3(0, 0, -1);
  vec3 vup = vec3(0, 1, 0);

private:
  int image_height;   // Rendered image height
  point3 center;      // Camera center
  point3 pixel00_loc; // Location of pixel 0, 0
  vec3 pixel_delta_u; // Offset to pixel to the right
  vec3 pixel_delta_v; // Offset to pixel below
  double sample_scale_per_pixel;
  vec3 u, v, w;

public:
  void render(const hittable &world) {
    initialize();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
      std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
                << std::flush;
      for (int i = 0; i < image_width; i++) {
        color pixel_color;
        for (int sample = 0; sample < sample_per_pixel; sample++) {
          Ray r = get_ray(i, j);
          pixel_color += ray_color(r, maxDepth, world);
        }
        write_color(std::cout, pixel_color * sample_scale_per_pixel);
      }
    }

    std::clog << "\rDone.                 \n";
  }

private:
  void initialize() {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = lookfrom;
    sample_scale_per_pixel = 1.0 / sample_per_pixel;

    // Determine viewport dimensions.
    double focal_length = (lookfrom - lookat).Length();
    double theta = degrees_to_radians(vfov / 2);
    double h = std::tan(theta);
    double viewport_height = 2.0 * h * focal_length;
    double viewport_width =
        viewport_height * (double(image_width) / image_height);

    w = unit_vector(lookfrom - lookat);
    u = cross(vup, w);
    v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical
    // viewport edges.
    vec3 viewport_u = viewport_width * u;
    vec3 viewport_v = viewport_height * -v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    vec3 viewport_upper_left =
        center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  }

  Ray get_ray(int i, int j) const {
    // Construct a camera ray originating from the origin and directed at
    // randomly sampled point around the pixel location i, j.

    auto offset = sample_square();
    auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) +
                        ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = center;
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
  }

  vec3 sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit
    // square.
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
  }

  color ray_color(const Ray &r, int depth, const hittable &world) {

    if (depth <= 0)
      return color(0, 0, 0);

    hit_record rec;
    if (world.hit(r, interval(0.0001, infinity), rec)) {
      // vec3 direction = random_on_hemisphere(rec.normal);
      // vec3 direction = rec.normal + random_unit_vector();
      // return 0.1 * ray_color(Ray(rec.p, direction), depth - 1, world);
      Ray scatter;
      vec3 attenuation;

      if (rec.mat->scatter(r, rec, attenuation, scatter))
        return attenuation * ray_color(scatter, depth - 1, world);

      return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};
