#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
private:
  vec3 orig;
  vec3 dir;

public:
  Ray() {}

  Ray(const vec3 &o, const vec3 &d) : orig(o), dir(d) {}

  const point3 &origin() const { return orig; }
  const vec3 &direction() const { return dir; }

  point3 at(double t) const { return orig + t * dir; }
};

#endif // !RAY_H
