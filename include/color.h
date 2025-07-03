#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include "interval.h"
#include <cmath>
#include <iostream>

using color = vec3;

inline double linear_to_gamma(const double linear_component) {
  if (linear_component > 0)
    return std::sqrt(linear_component);

  return 0;
}

void write_color(std::ostream &out, const color &pixel_color) {
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  interval interv(0, 0.9999);
  int ir = int(256 * interv.clamp(r));
  int ig = int(256 * interv.clamp(g));
  int ib = int(256 * interv.clamp(b));

  out << ir << " " << ig << " " << ib << " \n";
}

#endif // !COLOR_H
