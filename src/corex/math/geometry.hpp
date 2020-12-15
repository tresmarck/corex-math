#ifndef COREX_MATH_GEOMETRY_HPP
#define COREX_MATH_GEOMETRY_HPP

namespace cx
{
  float degreesToRadians(float degrees);
  float radiansToDegrees(float radians);
  float distance2D(const Point& start, const Point& end);
  float lineLength(const Line& line);
}

#endif
