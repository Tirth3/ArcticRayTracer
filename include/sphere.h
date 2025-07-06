#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "hittable.h"
#include "material.h"
#include <memory>

class sphere : public hittable {
public:
  sphere() {};
  sphere(point3 c, double rad) : center(c), radius(rad) {}
  sphere(point3 c, double rad, std::shared_ptr<material> m)
      : center(c), radius(rad), mat(m) {
    vec3 rvec = vec3(radius, radius, radius);
    bbox = aabb(center - rvec, center + rvec);
  }

  bool hit(const Ray &r, interval ray_t, hit_record &rec) const override {
    vec3 oc = center - r.origin();
    double a = r.direction().Length_Squared();
    double b = dot(r.direction(), oc);
    double c = oc.Length_Squared() - radius * radius;
    double discriminant = b * b - a * c;

    if (discriminant < 0.0)
      return false;

    double sqrtd = std::sqrt(discriminant);
    // Find the nearest root that lies in the acceptable range.
    double root = (b - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
      root = (b + sqrtd) / a;
      if (!ray_t.surrounds(root))
        return false;
    }

    rec.t = root;
    rec.p = r.at(root);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;

    return true;
  }

  aabb bounding_box() const override { return bbox; }

private:
  point3 center;
  double radius;
  std::shared_ptr<material> mat;
  aabb bbox;
};
#endif // !SPHERE_H
