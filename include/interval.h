#ifndef INTERVAL_H
#define INTERVAL_H

#include <cmath>
class interval {
public:
  double min, max;

  interval() : min(-INFINITY), max(INFINITY) {}

  interval(double tmin, double tmax) : min(tmin), max(tmax) {}

  double size() const { return (max - min); }

  bool contains(double x) const { return (min <= x && x <= max); }

  bool surrounds(double x) const { return (min < x && x < max); }

  double clamp(double x) const {
    if (x < min)
      return min;
    if (x > max)
      return max;
    return x;
  }
  static const interval empty, universe;
};

const interval interval::empty = interval(INFINITY, -INFINITY);
const interval interval::universe = interval(-INFINITY, INFINITY);

#endif // !INTERVAL_H
#define INTERVAL_H
