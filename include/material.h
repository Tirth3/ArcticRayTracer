#ifndef MATERIAL_H
#define MATERIAL_H

#include "ABConst.h"
#include "Vec3.h"
#include "color.h"
#include "hittable.h"
#include "ray.h"
#include <cmath>

class material {

public:
  virtual ~material() = default;

  virtual bool scatter(const Ray &ray_t, const hit_record &rec,
                       color &attenuation, Ray &scattered) const {
    return false;
  }
};

class lambertian : public material {
public:
  lambertian(const color &albedo) : albedo(albedo) {}

  bool scatter(const Ray &r_in, const hit_record &rec, color &attenuation,
               Ray &scattered) const override {
    auto scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero())
      scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

private:
  color albedo;
};

class metal : public material {
public:
  metal(const color &albedo, const double r) : albedo(albedo), roughness(r) {}

  bool scatter(const Ray &r_in, const hit_record &rec, color &attenuation,
               Ray &scattered) const override {
    vec3 reflected = unit_vector(reflect(r_in.direction(), rec.normal)) +
                     (roughness * random_unit_vector());
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return true;
  }

private:
  color albedo;
  double roughness;
};

class dielectric : public material {
public:
  dielectric(double refraction_index) : refraction_index(refraction_index) {}

  bool scatter(const Ray &r_in, const hit_record &rec, color &attenuation,
               Ray &scattered) const override {
    attenuation = color(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

    vec3 unit_direction = unit_vector(r_in.direction());

    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    vec3 direction;

    if (ri * sin_theta > 1.0)
      direction = reflect(unit_direction, rec.normal);
    else
      direction = refract(unit_direction, rec.normal, ri);

    direction = unit_vector(direction) + (roughness * random_unit_vector());

    scattered = Ray(rec.p, direction);
    return true;
  }

private:
  // Refractive index in vacuum or air, or the ratio of the material's
  // refractive index over the refractive index of the enclosing media
  double refraction_index;
  double roughness = 0.0;
};

#endif // !MATERIAL_H
#define MATERIAL_H
