#ifndef COREX_MATH_UTILS_HPP
#define COREX_MATH_UTILS_HPP

#include <cmath>
#include <type_traits>

#include <EASTL/vector.h>

#include <corex/math/algebra.hpp>
#include <corex/math/ds.hpp>

namespace cx
{
  template <typename T,
            std::enable_if_t<std::is_floating_point<T>::value, bool> = true
  >
  T setDecPlaces(T n, int numDecPlaces)
  {
    // We're using a custom pow() because std::pow() is slow.
    int multiplier = cx::pow(10, numDecPlaces);
    return roundf(n * static_cast<float>(multiplier)) / multiplier;
  }

  Polygon<4> convertRectangleToPolygon(const Rectangle& rect);
  Line longestLine(const eastl::vector<Line*> lines);

  template <uint32_t numVertices>
  eastl::array<Line, numVertices>
  convertPolygonToLines(const Polygon<numVertices>& polygon)
  {
    // The polygon passed is assumed to contain the points in a consecutive
    // manner.
    eastl::array<Line, numVertices> lines;
    for (int32_t i = 0; i < numVertices; i++) {
      lines[i] = Line{polygon.vertices[i],
                      polygon.vertices[(i + 1) % numVertices]};
    }

    return lines;
  }

  template <uint32_t numVertices>
  NPolygon convertPolygonToNPolygon(const Polygon<numVertices>& polygon)
  {
    NPolygon nPolygon;
    for (auto& vertex : polygon.vertices) {
      nPolygon.vertices.push_back(vertex);
    }

    return nPolygon;
  }
}

#endif
