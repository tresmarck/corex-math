#include <EASTL/vector.h>

#include <corex/math/ds.hpp>
#include <corex/math/geometry.hpp>
#include <corex/math/utils.hpp>
#include <corex/utils.hpp>

namespace cx
{
  Polygon<4> convertRectangleToPolygon(const Rectangle& rect)
  {
    // Should we just forward this instead of performing a function call?
    return rotateRectangle(rect.x, rect.y, rect.width, rect.height, rect.angle);
  }

  Line longestLine(const eastl::vector<Line*> lines)
  {
    // We don't want copies and references can't hold null objects.
    Line* longestLine = nullptr;
    bool isFirstElement = true;
    for (Line* line : lines) {
      if (isFirstElement
          || floatGreater(lineLength(*line), lineLength(*longestLine))) {
        // Let's utilize boolean short-circuit.
        isFirstElement = false;
        longestLine = line;
      }
    }

    return *longestLine;
  }
}
