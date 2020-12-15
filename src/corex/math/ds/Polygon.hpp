#ifndef COREX_MATH_DS_POLYGON_HPP
#define COREX_MATH_DS_POLYGON_HPP

#include <EASTL/array.h>

#include <corex/math/ds/Point.hpp>

namespace cx
{
  template <uint numVertices>
  struct Polygon
  {
    eastl::array<Point, numVertices> vertices;
  };
}

#endif
