#ifndef COREX_MATH_DS_LINE_SEGMENTS_HPP
#define COREX_MATH_DS_LINE_SEGMENTS_HPP

#include <EASTL/vector.h>

#include <corex/math/ds/Point.hpp>

namespace cx
{
  struct LineSegments
  {
    eastl::vector<Point> vertices;
  };
}

#endif
