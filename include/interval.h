#ifndef INTERVAL_H
#define INTERVAL_H

#include <cmath>
class interval {
public:
  double min, max;

  interval() : min(-INFINITY), max(INFINITY) {}

  interval(double tmin, double tmax) : min(tmin), max(tmax) {}

  interval(const interval &a, const interval &b) {
    // Create the interval tightly enclosing the two input intervals.
    min = a.min <= b.min ? a.min : b.min;
    max = a.max >= b.max ? a.max : b.max;
  }

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

  interval expand(const double delta) {
    double padding = delta / 2;
    return interval(min - padding, max + padding);
  }
  static const interval empty, universe;
};

const interval interval::empty = interval(INFINITY, -INFINITY);
const interval interval::universe = interval(-INFINITY, INFINITY);

#endif // !INTERVAL_H
#define INTERVAL_H
