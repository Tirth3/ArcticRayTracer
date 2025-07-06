#ifndef VEC3_H
#define VEC3_H

#include "ABConst.h"

class vec3 {
public:
  double e[3];

public:
  vec3() {
    e[0] = 0;
    e[1] = 0;
    e[2] = 0;
  }

  vec3(double e1, double e2, double e3) : e{e1, e2, e3} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  vec3 operator-() const { return {-e[0], -e[1], -e[2]}; }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  vec3 operator+=(vec3 v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vec3 operator*=(vec3 v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
  }

  vec3 operator/=(vec3 v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
  }

  double Length() const { return std::sqrt(Length_Squared()); }

  double Length_Squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  inline bool near_zero() const {
    double s = 10e-8;
    return (e[0] < s) && (e[1] < s) && (e[2] < s);
  }

  static vec3 Random_vector() {
    return {random_double(), random_double(), random_double()};
  }

  static vec3 Random_vector(const double tmin, const double tmax) {
    return {random_double(tmin, tmax), random_double(tmin, tmax),
            random_double(tmin, tmax)};
  }

  static vec3 random() {
    return vec3(random_double(), random_double(), random_double());
  }

  static vec3 random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max),
                random_double(min, max));
  }

private:
};

using point3 = vec3;

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline vec3 operator*(const vec3 &u, double t) {
  return {u.e[0] * t, u.e[1] * t, u.e[2] * t};
}

inline vec3 operator*(double t, const vec3 &u) {
  return {u.e[0] * t, u.e[1] * t, u.e[2] * t};
}
inline vec3 operator/(const vec3 &u, const vec3 &v) {
  return {u.e[0] / v.e[0], u.e[1] / v.e[1], u.e[2] / v.e[2]};
}

inline vec3 operator/(const vec3 &u, double t) { return (1.0 / t) * u; }

inline double dot(const vec3 &u, const vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3 &u) { return u / u.Length(); }

inline vec3 random_unit_vector() {
  while (true) {
    auto p = vec3::Random_vector(-1, 1);
    auto lensq = p.Length_Squared();
    if (1e-160 < lensq && lensq <= 1)
      return p / sqrt(lensq);
  }
}

inline vec3 random_on_hemisphere(const vec3 &normal) {
  vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}

inline vec3 reflect(const vec3 &v, const vec3 &n) {
  return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3 &uv, const vec3 &n, const double etai_by_eta) {
  double cos_theta = std::fmin(dot(-uv, n), 1.0);
  vec3 r_out_perp = etai_by_eta * (uv + cos_theta * n);
  vec3 r_out_parallel =
      -std::sqrt(std::fabs(1.0 - r_out_perp.Length_Squared())) * n;
  return r_out_perp + r_out_parallel;
}

#endif // !VEC3_H
