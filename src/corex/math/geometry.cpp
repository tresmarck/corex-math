#include <cmath>

#include <corex/math/algebra.hpp>
#include <corex/math/constants.hpp>
#include <corex/math/ds.hpp>
#include <corex/math/geometry.hpp>

namespace cx
{
  float degreesToRadians(float degrees)
  {
    return static_cast<float>(degrees * (pi / 180.0));
  }

  float radiansToDegrees(float radians)
  {
    return static_cast<float>(radians * (180.0 / pi));
  }

  float distance2D(const Point& start, const Point& end)
  {
    return sqrt(cx::pow(end.x - start.x, 2) + cx::pow(end.y - start.y, 2));
  }

  float lineLength(const Line& line)
  {
    return distance2D(line.start, line.end);
  }
}
